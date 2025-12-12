cmake_minimum_required(VERSION 3.10)

project(cromio VERSION 0.0.1 LANGUAGES C CXX)

# ============================================================
#                  MACOS & LLVM SETUP
# ============================================================

# Set macOS deployment target
set(CMAKE_OSX_DEPLOYMENT_TARGET "26.0")

# LLVM installed via Homebrew
set(LLVM_ROOT "/opt/homebrew/opt/llvm")
list(APPEND CMAKE_PREFIX_PATH "${LLVM_ROOT}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use system compilers (not LLVM's bundled compilers)
# This avoids C++ ABI conflicts
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

# ---- Path Definitions ----
set(GENERATED_DIR "${CMAKE_SOURCE_DIR}/src/parser/generated")
set(SOURCES_DIR "${CMAKE_SOURCE_DIR}/src")

# ---- ANTLR4 runtime include and lib paths ----
set(ANTLR4_RUNTIME_INCLUDE "/usr/local/include/antlr4-runtime")
set(ANTLR4_RUNTIME_LIB "${CMAKE_SOURCE_DIR}/antlr4/runtime/Cpp/build/runtime")

# ============================================================
#                     LLVM INTEGRATION
# ============================================================

cmake_policy(SET CMP0075 NEW)
cmake_policy(SET CMP0074 NEW)

# Enable RTTI for LLVM targets
set(LLVM_ENABLE_RTTI ON)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "LLVM include dirs: ${LLVM_INCLUDE_DIRS}")

# Map all LLVM components your project uses
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

# LLVM compilation flags
add_definitions(${LLVM_DEFINITIONS})

# Force include paths for LLVM
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
include_directories(SYSTEM "${LLVM_ROOT}/include")

# Add explicit compile flags
add_compile_options(-I${LLVM_ROOT}/include)

# ============================================================
#                 Collect Sources & Executable
# ============================================================
file(GLOB_RECURSE ALL_SOURCES
        "${SOURCES_DIR}/cromio.cpp"
        "${GENERATED_DIR}/*.cpp"
        "${SOURCES_DIR}/*.cpp"
        "${SOURCES_DIR}/utils/*.cpp"
        "${SOURCES_DIR}/visitor/*.cpp"
        "${SOURCES_DIR}/optimizer/*.cpp"
        "${SOURCES_DIR}/backend/*.cpp"
        "${SOURCES_DIR}/core/*.cpp"
        "${SOURCES_DIR}/semantic/*.cpp"
        "${SOURCES_DIR}/modules/*.cpp"
)

add_executable(${PROJECT_NAME} ${ALL_SOURCES})

# ============================================================
#                     Target Setup
# ============================================================
# Project & ANTLR includes
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}
        ${SOURCES_DIR}
        ${ANTLR4_RUNTIME_INCLUDE}
        ${GENERATED_DIR}
)

# LLVM includes (SYSTEM suppresses warnings)
target_include_directories(${PROJECT_NAME} SYSTEM BEFORE PUBLIC
        ${LLVM_INCLUDE_DIRS}
        ${LLVM_ROOT}/include
)

# Link directories (for ANTLR)
target_link_directories(${PROJECT_NAME} PUBLIC
        ${ANTLR4_RUNTIME_LIB}
        ${LLVM_ROOT}/lib
)

# Suppress duplicate library warnings
target_link_options(${PROJECT_NAME} PRIVATE "LINKER:-no_warn_duplicate_libraries")

# Link ANTLR and LLVM libraries
target_link_libraries(${PROJECT_NAME}
        antlr4-runtime
        "${ANTLR4_RUNTIME_LIB}/libantlr4-runtime.4.13.2.dylib"
        ${llvm_libs}
)

# ============================================================
#                   Custom "make run"
# ============================================================
set(DEFAULT_FILE "${CMAKE_SOURCE_DIR}/test.io")

add_custom_target(run
        COMMAND ${PROJECT_NAME} ${DEFAULT_FILE}
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)