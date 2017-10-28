cmake_minimum_required(VERSION 3.8)
project(assignment1)

set(CMAKE_C_STANDARD 90)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES ass1.c)
add_executable(assignment1 ${SOURCE_FILES})