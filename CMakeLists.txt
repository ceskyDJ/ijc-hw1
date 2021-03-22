cmake_minimum_required(VERSION 3.17)
project(IJC\ |\ 1st\ homework C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -pedantic -Wall -Wextra -fsanitize=address -DUSE_INLINE -lm -O2")

add_executable(primes bitset.c bitset.h eratosthenes.c eratosthenes.h error.c error.h primes.c)
add_executable(steg-decode bitset.c bitset.h eratosthenes.c eratosthenes.h error.c error.h ppm.c ppm.h steg-decode.c)
