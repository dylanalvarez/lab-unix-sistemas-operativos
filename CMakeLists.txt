cmake_minimum_required(VERSION 3.5)
project(lab-unix-1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wextra -Wpedantic -std=c11")
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(rm0.bin rm0/main.c)
add_executable(cat0.bin cat0/main.c)
