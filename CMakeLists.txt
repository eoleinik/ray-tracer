cmake_minimum_required(VERSION 3.6)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp vec3.cpp vec3.h)
add_executable(ray_tracer ${SOURCE_FILES})