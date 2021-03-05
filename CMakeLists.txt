cmake_minimum_required(VERSION 3.17)
project(IJC\ |\ 1.\ homework C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -pedantic -Wall -Wextra -fsanitize=address")

add_executable(DU1 bitset.h primes.c error.c error.h ppm.c ppm.h eratosthenes.c steg-decode.c)