cmake_minimum_required(VERSION 3.10)

project(yogi VERSION 0.0.1 LANGUAGES C CXX)

# ============================================================
#                       OPTIONS
# ============================================================
option(ENABLE_TESTING "Build test executable" OFF)
option(ENABLE_TESTING_FOR_TYPES_HINTS "Build test executable" ON)

# ============================================================
#                  MACOS & LLVM SETUP
# ============================================================
set(CMAKE_OSX_DEPLOYMENT_TARGET "26.0")

set(LLVM_ROOT "/opt/homebrew/opt/llvm")
list(APPEND CMAKE_PREFIX_PATH "${LLVM_ROOT}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

# ============================================================
#                       PATHS
# ============================================================
set(GENERATED_DIR "${CMAKE_SOURCE_DIR}/src/parser/generated")
set(SOURCES_DIR "${CMAKE_SOURCE_DIR}/src")
set(TESTS_DIR "${CMAKE_SOURCE_DIR}/tests")
set(LIBS_DIR "${CMAKE_SOURCE_DIR}/libs")

set(ANTLR4_RUNTIME_INCLUDE "/usr/local/include/antlr4-runtime")
set(ANTLR4_RUNTIME_LIB "${CMAKE_SOURCE_DIR}/libs/antlr4/runtime/Cpp/build/runtime")

# ============================================================
#                       LLVM
# ============================================================
cmake_policy(SET CMP0075 NEW)
cmake_policy(SET CMP0074 NEW)

set(LLVM_ENABLE_RTTI ON)
find_package(LLVM REQUIRED CONFIG)

llvm_map_components_to_libnames(llvm_libs
        core
        support
        native
        irreader
        linker
        bitreader
        bitwriter
        target
        targetparser
        mc
        mcparser
        x86codegen
        aarch64codegen
)

add_definitions(${LLVM_DEFINITIONS})

# ============================================================
#                PRODUCTION SOURCES & EXECUTABLE
# ============================================================
if (NOT ENABLE_TESTING)
    IF (ENABLE_TESTING_FOR_TYPES_HINTS)
        file(GLOB_RECURSE PROD_SOURCES
                "${SOURCES_DIR}/*.cpp"
                "${GENERATED_DIR}/*.cpp"
                "${TESTS_DIR}/*.cpp"
        )
        add_executable(yogi ${PROD_SOURCES})
    ENDIF ()

    IF (NOT ENABLE_TESTING_FOR_TYPES_HINTS)
        file(GLOB_RECURSE PROD_SOURCES
                "${SOURCES_DIR}/*.cpp"
                "${GENERATED_DIR}/*.cpp"
        )
        add_executable(yogi ${PROD_SOURCES})
    ENDIF ()


    target_include_directories(yogi PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${SOURCES_DIR}
            ${GENERATED_DIR}
            ${LIBS_DIR}
            ${ANTLR4_RUNTIME_INCLUDE}
            ${LLVM_INCLUDE_DIRS}
            ${LLVM_ROOT}/include
    )

    target_link_directories(yogi PRIVATE
            ${ANTLR4_RUNTIME_LIB}
            ${LLVM_ROOT}/lib
    )

    target_link_options(yogi PRIVATE "LINKER:-no_warn_duplicate_libraries")

    target_link_libraries(yogi
            antlr4-runtime
            "${ANTLR4_RUNTIME_LIB}/libantlr4-runtime.4.13.2.dylib"
            ${llvm_libs}
    )

    # ============================================================
    #                       RUN TARGET
    # ============================================================
    set(DEFAULT_FILE "${CMAKE_SOURCE_DIR}/test.io")

    add_custom_target(run
            COMMAND yogi ${DEFAULT_FILE}
            DEPENDS yogi
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif ()

# ============================================================
#                     TEST EXECUTABLE
# ============================================================
if (ENABLE_TESTING)
    file(GLOB TEST_SOURCES "${TESTS_DIR}/*.cpp")

    # Get all production sources except the file with main()
    file(GLOB_RECURSE PROD_SOURCES_NO_MAIN
            "${SOURCES_DIR}/*.cpp"
            "${GENERATED_DIR}/*.cpp"
            "${TESTS_DIR}/*.cpp"
    )
    # Exclude both main.cpp and yogi.cpp (whichever contains main)
    list(FILTER PROD_SOURCES_NO_MAIN EXCLUDE REGEX ".*(main|yogi)\\.cpp$")

    add_executable(yogi_tests
            ${TEST_SOURCES}
            ${PROD_SOURCES_NO_MAIN}
            ${CMAKE_SOURCE_DIR}/libs/catch2/catch_amalgamated.cpp
    )

    target_include_directories(yogi_tests PRIVATE
            ${CMAKE_SOURCE_DIR}
            ${SOURCES_DIR}
            ${TESTS_DIR}
            ${GENERATED_DIR}
            ${LIBS_DIR}
            ${CMAKE_SOURCE_DIR}/external/catch2
            ${ANTLR4_RUNTIME_INCLUDE}
            ${LLVM_INCLUDE_DIRS}
            ${LLVM_ROOT}/include
    )

    target_link_directories(yogi_tests PRIVATE
            ${ANTLR4_RUNTIME_LIB}
            ${LLVM_ROOT}/lib
    )

    target_link_options(yogi_tests PRIVATE "LINKER:-no_warn_duplicate_libraries")

    target_link_libraries(yogi_tests
            antlr4-runtime
            "${ANTLR4_RUNTIME_LIB}/libantlr4-runtime.4.13.2.dylib"
            ${llvm_libs}
    )

    add_custom_target(run-tests
            COMMAND yogi_tests
            DEPENDS yogi_tests
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif ()