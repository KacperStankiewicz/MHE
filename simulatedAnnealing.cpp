//
// Created by Kapa on 07.05.2023.
//

#include <iostream>
#include "simulatedAnnealing.h"

namespace mhe {
    //todo: normal distribution
    solution_t
    simulatedAnnealing(const solution_t &solution, const std::function<double(int)> &temperature, int numOfIterations,
                       std::mt19937 &rgen) {
        solution_t globalBest = solution;
        solution_t currentSolution = solution;

        for (int i = 0; i < numOfIterations; i++) {
            solution_t newSolution = currentSolution.randomModify(rgen);

            if (newSolution.goal() <= currentSolution.goal()) {
                currentSolution = newSolution;

                if (newSolution.goal() <= globalBest.goal()) {
                    globalBest = newSolution;
                    std::cout << "ANNEALING\n" << "iteration: " << i << std::endl << globalBest;
                }
            } else {
                std::uniform_real_distribution<double> distr(0.0, 1.0);
                if (distr(rgen) < std::exp(-std::abs(newSolution.goal() - currentSolution.goal()) / temperature(i))) {
                    currentSolution = newSolution;
                }
            }
        }
        return globalBest;
    }
} // mhe