cmake_minimum_required(VERSION 3.10)
project(yogi_runtime)

include_directories(includes)
add_library(${PROJECT_NAME} STATIC src/str.cpp)


