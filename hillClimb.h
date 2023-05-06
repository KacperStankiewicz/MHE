//
// Created by Kapa on 02.04.2023.
//

#ifndef PROJEKT_HILLCLIMB_H
#define PROJEKT_HILLCLIMB_H

#include "solution_t.h"
#include "random"
#include "utils.h"

namespace mhe {

    solution_t randomHillClimb(solution_t solution, int numOfIterations, std::mt19937 &rgen);

    solution_t deterministicHillClimb(solution_t solution, int numOfIterations);

} // mhe

#endif //PROJEKT_HILLCLIMB_H
