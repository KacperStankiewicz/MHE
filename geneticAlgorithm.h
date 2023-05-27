//
// Created by Kapa on 27.05.2023.
//

#ifndef PROJEKT_GENETICALGORITHM_H
#define PROJEKT_GENETICALGORITHM_H

#include "threePartitionProblemGaConfig.h"
#include "solution_t.h"

namespace mhe {
    solution_t geneticAlgorithm(threePartitionProblemGaConfig &config, std::mt19937 &rgen);

    std::vector<solution_t> leastElementsMutation(std::vector<solution_t> population, std::mt19937 &rgen);

    std::vector<solution_t> mutation(std::vector<solution_t> population, std::mt19937 &rgen);

    std::vector<solution_t> crossover(std::vector<solution_t> population, std::mt19937 &rgen);

    std::pair<solution_t, solution_t> onePointCrossover(solution_t a, solution_t b, std::mt19937 &rgen);

    std::pair<solution_t, solution_t> uniformCrossover(solution_t a, solution_t b, std::mt19937 &rgen);

    std::vector<solution_t>
    rouletteWheelSelection(std::vector<double> fitnesses, std::vector<solution_t> population, std::mt19937 &rgen);

} //mhe
#endif //PROJEKT_GENETICALGORITHM_H
