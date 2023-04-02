//
// Created by Kapa on 02.04.2023.
//

#ifndef PROJEKT_PROBLEM_T_H
#define PROJEKT_PROBLEM_T_H

#include <array>
#include <vector>
#include <random>
#include "utils.h"

namespace mhe {
    using problem_t = std::array<std::vector<int>, 3>;
    mhe::problem_t generateProblem(int length, int min, int max, std::mt19937 &rgen);
    void adjustVectorToBeDivisibleBy3(problem_t &problem);
    std::ostream &operator<<(std::ostream &o, const problem_t v);
} // mhe

#endif //PROJEKT_PROBLEM_T_H
