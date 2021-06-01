cmake_minimum_required(VERSION 3.17)
project(fibonacci)

set(CMAKE_CXX_STANDARD 20)

add_executable(fibonacci main.cpp memoize.h)