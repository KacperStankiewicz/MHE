cmake_minimum_required(VERSION 3.24)
project(projekt)

set(CMAKE_CXX_STANDARD 17)

add_executable(projekt main.cpp problemGenerator.cpp problemGenerator.h solution_t.cpp solution_t.h)
