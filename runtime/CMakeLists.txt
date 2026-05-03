cmake_minimum_required(VERSION 3.10)

project(yogi_runtime)

file(GLOB RUNTIME_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(yogi_runtime STATIC
        ${RUNTIME_SOURCES}
)

target_include_directories(yogi_runtime PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

