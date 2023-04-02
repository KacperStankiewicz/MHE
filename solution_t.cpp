//
// Created by Kapa on 25.03.2023.
//

#include <numeric>
#include <ostream>
#include "solution_t.h"

namespace mhe {

    solution_t solution_t::forProblem(problem_t problem){
        solution_t solution;
        solution.problem = std::make_shared<problem_t>(problem);
        solution.goal_sum = std::accumulate(solution.problem->begin(), solution.problem->end(), 0, [](auto l, auto r){
            return std::accumulate(r.begin(), r.end(), l);
        }) /3;
        return solution;
    }

    int solution_t::goal() const {
        int difference = 0;

        for (int i = 0; i < 3; i++) {
            int sum = 0;
            for (auto e: this->problem->at(i)) {
                sum += e;
            }
            difference += std::abs(goal_sum - sum);
        }
        return difference;
    }

    std::ostream &operator<<(std::ostream &o, const mhe::solution_t s) {
        o << *s.problem;
        o << "goal = " << s.goal() << std::endl << "--------------------------------------------" << std::endl;

        return o;
    }
} // mhe