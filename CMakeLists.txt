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
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(LLVM_ROOT "/opt/homebrew/opt/llvm")
list(APPEND CMAKE_PREFIX_PATH "${LLVM_ROOT}")

# ============================================================
#                       PATHS
# ============================================================
set(GENERATED_DIR "${CMAKE_SOURCE_DIR}/src/antlr/generated")
set(SOURCES_DIR "${CMAKE_SOURCE_DIR}/src")
set(TESTS_DIR "${CMAKE_SOURCE_DIR}/tests")
set(LIBS_DIR "${CMAKE_SOURCE_DIR}/libs")

set(SOURCES_PAST "${CMAKE_SOURCE_DIR}/past")
set(SOURCES_LINKER "${CMAKE_SOURCE_DIR}/linker")
set(SOURCES_COMPILER "${CMAKE_SOURCE_DIR}/compiler")


set(ANTLR4_RUNTIME_INCLUDE "/usr/local/include/antlr4-runtime")
set(ANTLR4_RUNTIME_LIB "${CMAKE_SOURCE_DIR}/libs/antlr4/runtime/Cpp/build/runtime")


# ============================================================
#                       RUNTIME
# ============================================================
add_subdirectory(runtime)



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

file(GLOB_RECURSE PROD_SOURCES
    "${SOURCES_DIR}/*.cpp"
    "${GENERATED_DIR}/*.cpp"
)


add_executable(yogi ${PROD_SOURCES})

target_include_directories(yogi PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/runtime/includes
    ${SOURCES_DIR}
    ${SOURCES_PAST}
    ${SOURCES_LINKER}
    ${SOURCES_COMPILER}
    ${GENERATED_DIR}
    ${LIBS_DIR}
    ${ANTLR4_RUNTIME_INCLUDE}
    ${LLVM_INCLUDE_DIRS}
    ${LLVM_ROOT}/include
    ${LIBS_DIR}/uni-algo/include
    ${LIBS_DIR}/uni-algo/include
)

target_link_directories(yogi PRIVATE
    ${ANTLR4_RUNTIME_LIB}
    ${LLVM_ROOT}/lib
)

target_link_options(yogi PRIVATE
"-Wl,-w"
)

target_link_libraries(yogi PRIVATE
    yogi_runtime
    antlr4-runtime
    "${ANTLR4_RUNTIME_LIB}/libantlr4-runtime.4.13.2.dylib"
    "${LIBS_DIR}/uni-algo/build/libuni-algo.a"
    ${llvm_libs}
)

add_custom_target(run
    DEPENDS yogi
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)