//
// Created by Kapa on 02.04.2023.
//

#include "problem_t.h"

namespace mhe {

    //todo: *for new problem type* maybe this could be adjusted to return only doable problems?

    mhe::problem_t generateProblem(int length, int min, int max, std::mt19937 &rgen) {
        using namespace std;
        uniform_int_distribution<int> distr(min, max);
        problem_t result;
        for (int i = 0; i < length; i++) {
            result[i % 3].push_back(distr(rgen));
        }
        adjustVectorToBeDivisibleBy3(result);
        return result;
    }

    void adjustVectorToBeDivisibleBy3(problem_t &problem) {
        int sum = std::accumulate(problem.begin(), problem.end(), 0, [](auto l, auto r) {
            return std::accumulate(r.begin(), r.end(), l);
        });

        int remainder = sum % 3;
        int delta = (3 - remainder) % 3;
        if (delta != 0) {
            problem.at(2).back() += delta;
        }
    }

    std::ostream &operator<<(std::ostream &o, const problem_t v) {
        for (int i = 0; i < 3; i++) {
            o << "S" << i + 1 << "= { ";
            for (auto e: v[i]) {
                o << e << " ";
            }
            o << "}" << std::endl;
        }
        return o;
    }
} // mhe