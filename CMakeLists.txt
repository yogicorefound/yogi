cmake_minimum_required(VERSION 3.10)
project(yogi VERSION 0.0.1 LANGUAGES C CXX)

# ============================================================
#                  MACOS & LLVM SETUP
# ============================================================
set(CMAKE_OSX_DEPLOYMENT_TARGET "26.0")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# ANTLR4
set(ANTLR4_RUNTIME_INCLUDE "${CMAKE_SOURCE_DIR}/libs/antlr4/runtime/Cpp/runtime/src")
set(ANTLR4_RUNTIME_LIB "${CMAKE_SOURCE_DIR}/libs/antlr4/runtime/Cpp/build/runtime")

set(ANTLR_GENERATED_DIR "${CMAKE_SOURCE_DIR}/compiler/antlr/generated")
set(SOURCES_COMPILER "${CMAKE_SOURCE_DIR}/compiler")
set(LIBS_DIR "${CMAKE_SOURCE_DIR}/libs")

cmake_policy(SET CMP0075 NEW)
cmake_policy(SET CMP0074 NEW)

set(LLVM_ENABLE_RTTI ON)
set(LLVM_ROOT "/opt/homebrew/opt/llvm@21")

set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -Wl,-no_compact_unwind"
)

list(APPEND CMAKE_PREFIX_PATH "${LLVM_ROOT}")
find_package(LLVM REQUIRED CONFIG)
find_package(OpenSSL REQUIRED)

# ============================================================
# LLVM COMPONENTS (FIX: ORC/JIT ADDED)
# ============================================================
llvm_map_components_to_libnames(llvm_libs
        Core
        Support
        IRReader
        Linker
        BitReader
        BitWriter

        Target
        TargetParser

        MC
        MCParser
        MCJIT          # add this if you use MCJIT anywhere

        # x86
        X86CodeGen
        X86AsmParser   # <-- add
        X86Desc        # <-- add
        X86Info        # <-- add

        # AArch64
        AArch64CodeGen
        AArch64AsmParser   # <-- THIS is what's missing
        AArch64Desc        # <-- add
        AArch64Info        # <-- add
        AArch64Utils       # <-- add

        # ORC / JIT
        OrcJIT
        OrcShared
        OrcTargetProcess
        JITLink
        ExecutionEngine
)

add_definitions(${LLVM_DEFINITIONS})

file(GLOB_RECURSE PROD_SOURCES
        "${SOURCES_COMPILER}/*.cpp"
        "${ANTLR_GENERATED_DIR}/*.cpp"
        "${CMAKE_SOURCE_DIR}/yogi/*.cpp"
)

# ============================================================
#                       RUNTIME
# ============================================================
add_subdirectory(runtime)
include_directories(yogi_runtime)

add_executable(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${PROD_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${SOURCES_COMPILER}
        ${ANTLR_GENERATED_DIR}
        ${ANTLR4_RUNTIME_INCLUDE}
        ${LLVM_ROOT}/include
        ${LIBS_DIR}/uni-algo/include
        ${LIBS_DIR}
)


target_link_libraries(${PROJECT_NAME} PRIVATE
        "${ANTLR4_RUNTIME_LIB}/libantlr4-runtime.4.13.2.dylib"
        "${LIBS_DIR}/uni-algo/build/libuni-algo.a"
        ${llvm_libs}
        yogi_runtime
        OpenSSL::Crypto
)