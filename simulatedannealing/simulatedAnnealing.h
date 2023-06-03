//
// Created by Kapa on 07.05.2023.
//

#ifndef PROJEKT_SIMULATEDANNEALING_H
#define PROJEKT_SIMULATEDANNEALING_H

#include <random>
#include <functional>
#include "../solution/solution_t.h"

namespace mhe {

    solution_t
    simulatedAnnealing(const solution_t &solution, const std::function<double(int)> &temperature, int numOfIterations,
                       std::mt19937 &rgen);

} // mhe

#endif //PROJEKT_SIMULATEDANNEALING_H
