cmake_minimum_required(VERSION 3.5)
project(lab-unix)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wall -Wextra -Wpedantic -std=c11")
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(rm0.bin rm0/main.c)
add_executable(cat0.bin cat0/main.c)
add_executable(touch0.bin touch0/main.c)
add_executable(stat0.bin stat0/main.c)
add_executable(ln0.bin ln0/main.c)
add_executable(mv0.bin mv0/main.c)
add_executable(cp0.bin cp0/main.c)
