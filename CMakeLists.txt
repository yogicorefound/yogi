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
set(LLVM_ROOT "${LIBS_DIR}/llvm-project/build/llvm-custom")
add_definitions(-DLLD_PATH="${LLVM_ROOT}/bin/ld.lld")


# ============================================================
#                  LINKER FLAGS
# ============================================================
set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -Wl,-no_compact_unwind"
)

list(APPEND CMAKE_PREFIX_PATH "${LLVM_ROOT}")
find_package(OpenSSL REQUIRED)

# ============================================================
# FIND LLVM — loads llvm_map_components_to_libnames
# ============================================================
find_package(LLVM REQUIRED CONFIG
        PATHS "${LLVM_ROOT}/lib/cmake/llvm"
        NO_DEFAULT_PATH
)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION} at ${LLVM_DIR}")

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

# ============================================================
# LLVM COMPONENTS
# ============================================================
set(LLVM_COMPONENTS
        Core
        Support
        IRReader
        Linker

        Analysis
        InstCombine
        ScalarOpts
        TransformUtils
        IPO
        Object
        Passes

        BitReader
        BitWriter

        Target
        TargetParser

        MC
        MCParser

        X86CodeGen
        X86AsmParser
        X86Desc
        X86Info

        AArch64CodeGen
        AArch64AsmParser
        AArch64Desc
        AArch64Info
        AArch64Utils

        OrcJIT
        OrcShared
        OrcTargetProcess
        JITLink
        ExecutionEngine
)

llvm_map_components_to_libnames(llvm_libs ${LLVM_COMPONENTS})
list(REMOVE_DUPLICATES llvm_libs)

add_definitions(${LLVM_DEFINITIONS})

# ============================================================
#                  SOURCES
# ============================================================
file(GLOB_RECURSE PROD_SOURCES
        "${SOURCES_COMPILER}/*.cpp"
        "${ANTLR_GENERATED_DIR}/*.cpp"
        "${CMAKE_SOURCE_DIR}/yogi/*.cpp"
)

# ============================================================
#                       RUNTIME
# ============================================================
add_subdirectory(runtime)

# ============================================================
#                     EXECUTABLE
# ============================================================
add_executable(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${PROD_SOURCES}
)

# target_* calls must come AFTER add_executable
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${SOURCES_COMPILER}
        ${ANTLR_GENERATED_DIR}
        ${ANTLR4_RUNTIME_INCLUDE}
        ${LLVM_ROOT}/include
        ${LLVM_INCLUDE_DIRS}
        ${LIBS_DIR}/uni-algo/include
        ${LIBS_DIR}
)

target_link_directories(${PROJECT_NAME} PRIVATE
        ${LLVM_ROOT}/lib
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        "${ANTLR4_RUNTIME_LIB}/libantlr4-runtime.4.13.2.dylib"
        "${LIBS_DIR}/uni-algo/build/libuni-algo.a"
        ${llvm_libs}
        ${LLVM_ROOT}/lib/liblldCommon.a
        ${LLVM_ROOT}/lib/liblldELF.a
        ${LLVM_ROOT}/lib/liblldMachO.a
        yogi_runtime
        OpenSSL::Crypto
)