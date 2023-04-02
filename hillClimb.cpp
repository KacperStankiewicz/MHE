//
// Created by Kapa on 02.04.2023.
//

#include <iostream>
#include "hillClimb.h"
#include "random"

namespace mhe {
    solution_t randomHillClimb(solution_t solution, int numOfIterations, std::mt19937 &rgen) {
        //todo: make a copy of object solution, because now bestSolution and newSolution is the same place in memory, so /if/ always is true
        auto bestSolution = *new solution_t(solution);
        for (int i = 0; i < numOfIterations; i++) {
            auto newSolution = randomModify(solution, rgen);

            if (newSolution.goal() <= bestSolution.goal()) {
                bestSolution = newSolution;
                std::cout << "iteration: " << i << std::endl << bestSolution << " goal: " << bestSolution.goal()
                          << std::endl;
            }
        }
        return bestSolution;
    }

    solution_t randomModify(solution_t solution, std::mt19937 &rgen) {
        std::uniform_int_distribution<int> distr(0, 2);
        int from = distr(rgen);
        int to = distr(rgen);

        while (from == to) {
            to = distr(rgen);
        }

        while (solution.problem->at(from).empty()){
            from = distr(rgen);
        }

        distr = std::uniform_int_distribution<int>(0, solution.problem->at(from).size() - 1);
        int a = distr(rgen);

        solution.problem->at(to).push_back(solution.problem->at(from)[a]);
        solution.problem->at(from).erase(solution.problem->at(from).begin()+a);

        return solution;
    }
} // mhe