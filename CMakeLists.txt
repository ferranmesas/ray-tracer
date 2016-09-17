cmake_minimum_required(VERSION 3.2)
project(ray_tracer)

# TODO: autodetect lua location
find_package(LUA REQUIRED)

include_directories(${LUA_INCLUDE_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -std=c11")

set(SOURCE_FILES
    src/color.c
    src/color.h
    src/defines.h
    src/main.c
    src/material.c
    src/material.h
    src/point.c
    src/point.h
    src/ray.c
    src/ray.h
    src/scene.c
    src/scene.h
    src/utils.c
    src/utils.h)

add_executable(ray_tracer ${SOURCE_FILES})

target_link_libraries(ray_tracer ${LUA_LIBRARIES})
