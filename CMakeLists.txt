cmake_minimum_required(VERSION 3.5)
project(lab-unix-1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wextra -Wpedantic -std=c11")
set(CMAKE_VERBOSE_MAKEFILE ON)

set(RM0_SOURCE_FILES rm0/main.c)
add_executable(rm0.bin ${RM0_SOURCE_FILES})
