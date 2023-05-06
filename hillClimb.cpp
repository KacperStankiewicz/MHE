//
// Created by Kapa on 02.04.2023.
//

#include <iostream>
#include "hillClimb.h"
#include "random"

namespace mhe {
    solution_t randomHillClimb(solution_t solution, int numOfIterations, std::mt19937 &rgen) {
        for (int i = 0; i < numOfIterations; i++) {
            auto newSolution = solution.randomModify(rgen);

            if (newSolution.goal() <= solution.goal()) {
                solution = newSolution;
                std::cout << "iteration: " << i << std::endl << solution;
            }
        }
        return solution;
    }

    solution_t deterministicHillClimb(solution_t solution, int numOfIterations){
        for (int i = 0; i < numOfIterations; i++) {
            auto newSolution = solution.bestNeighbour();

            if (newSolution.goal() <= solution.goal()) {
                solution = newSolution;
                std::cout << "iteration: " << i << std::endl << solution;
            }
        }
        return solution;
    }
} // mhe