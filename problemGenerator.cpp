//
// Created by Kapa on 25.03.2023.
//

#include "problemGenerator.h"
#include <random>
#include <algorithm>

namespace mhe {

    std::vector<int> generateProblem(int length, int min, int max, std::mt19937 &rgen) {
        using namespace std;
        uniform_int_distribution<int> distr(min, max);
        vector<int> result;
        for (int i = 0; i < length; i++) {
            result.push_back(distr(rgen));
        }
        mhe::adjustVectorToBeDivisibleBy3(result);
        return result;
    }

    void adjustVectorToBeDivisibleBy3(std::vector<int> &vec) {
        int sum = accumulate(vec.begin(), vec.end(), 0);
        int remainder = sum % 3;
        int delta = (3 - remainder) % 3;
        if (delta != 0) {
            vec.back() += delta;
        }
    }

    std::ostream &operator<<(std::ostream &o, const std::vector<int> v) {
        o << "{ ";
        for (auto e: v)
            o << e << " ";
        o << "}";
        return o;
    }
} // mhe