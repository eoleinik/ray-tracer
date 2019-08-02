cmake_minimum_required(VERSION 3.6)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp vec3.h ray.h hitable.h sphere.h hitable_list.h camera.h material.h lambertian.h metal.h dielectric.h)
add_executable(ray_tracer ${SOURCE_FILES})
