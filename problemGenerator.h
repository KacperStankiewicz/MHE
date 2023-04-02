#ifndef PROJEKT_PROBLEMGENERATOR_H
#define PROJEKT_PROBLEMGENERATOR_H

#include <vector>
#include <random>
#include <iostream>

namespace mhe {
    std::vector<int> generateProblem(int length, int min, int max, std::mt19937 &rgen);
    std::ostream &operator<<(std::ostream &o, std::vector<int> v);
    void adjustVectorToBeDivisibleBy3(std::vector<int> &vec);
} // mhe

#endif //PROJEKT_PROBLEMGENERATOR_H
