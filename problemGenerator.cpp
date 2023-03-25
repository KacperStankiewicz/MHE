//
// Created by Kapa on 25.03.2023.
//

#include "problemGenerator.h"
#include <random>

namespace mhe {
    std::vector<int> generateProblem(int length, int min, int max, std::mt19937 &rgen) {
        //todo:: zmiana generowania, aby zbiory byly mozliwe do podzialu
        //vec[n - 1] = (3 - (sum % 3)) % 3;
        std::uniform_int_distribution<int> distr(min, max);
        std::vector<int> result;
        for (int i = 0; i < length; i++) {
            result.push_back(distr(rgen));
        }
        return result;
    }

    std::ostream &operator<<(std::ostream &o, const std::vector<int> v){
        o << "{ ";
        for (auto e: v)
            o << e << " ";
        o << "}";
        return o;
    }
} // mhe