//
// Created by Kapa on 13.05.2023.
//

#ifndef PROJEKT_THREEPARTITIONPROBLEMGACONFIG_H
#define PROJEKT_THREEPARTITIONPROBLEMGACONFIG_H

#include "../solution/solution_t.h"

namespace mhe {

    class threePartitionProblemGaConfig {
    public:
        int populationSize;
        int iteration;
        int maxIterations;
        double targetQuality;
        problem_t problem;

        threePartitionProblemGaConfig(int maxIter, int popSize, double quality, problem_t problem_) {
            maxIterations = maxIter;
            iteration = 0;
            populationSize = popSize;
            if (quality > 1.0) {
                targetQuality = 1.0;
            } else {
                targetQuality = quality;
            }
            problem = problem_;
        }
    };
} // mhe

#endif //PROJEKT_THREEPARTITIONPROBLEMGACONFIG_H
