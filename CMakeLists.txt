cmake_minimum_required(VERSION 3.24)
project(projekt)

set(CMAKE_CXX_STANDARD 20)

add_executable(projekt main.cpp solution/solution_t.cpp solution/solution_t.h hillclimb/hillClimb.cpp hillclimb/hillClimb.h utils/utils.cpp utils/utils.h solution/problem_t.cpp solution/problem_t.h tabu/tabuSearch.cpp tabu/tabuSearch.h simulatedannealing/simulatedAnnealing.cpp simulatedannealing/simulatedAnnealing.h geneticalgorithm/geneticAlgorithm.cpp geneticalgorithm/threePartitionProblemGaConfig.h geneticalgorithm/geneticAlgorithm.h)
