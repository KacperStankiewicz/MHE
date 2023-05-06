cmake_minimum_required(VERSION 3.24)
project(projekt)

set(CMAKE_CXX_STANDARD 20)

add_executable(projekt main.cpp solution_t.cpp solution_t.h hillClimb.cpp hillClimb.h utils.cpp utils.h problem_t.cpp problem_t.h tabuSearch.cpp tabuSearch.h)
