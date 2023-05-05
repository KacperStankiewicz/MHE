//
// Created by Kapa on 25.03.2023.
//

#include <numeric>
#include <ostream>
#include "solution_t.h"

namespace mhe {

    solution_t solution_t::forProblem(problem_t problem) {
        solution_t solution;
        solution.problem = std::make_shared<problem_t>(problem);
        solution.goal_sum = std::accumulate(solution.problem->begin(), solution.problem->end(), 0, [](auto l, auto r) {
            return std::accumulate(r.begin(), r.end(), l);
        }) / 3;
        solution.at(0) = problem.at(0);
        solution.at(1) = problem.at(1);
        solution.at(2) = problem.at(2);

        return solution;
    }

    int solution_t::goal() const {
        int difference = 0;

        for (int i = 0; i < 3; i++) {
            int sum = 0;
            for (auto e: this->at(i)) {
                sum += e;
            }
            difference += std::abs(goal_sum - sum);
        }
        return difference;
    }

    solution_t solution_t::randomModify(std::mt19937 &rgen) const {
        std::uniform_int_distribution<int> distr(0, 2);
        int from = distr(rgen);
        int to = distr(rgen);

        solution_t solution = *this;
        while (from == to) {
            to = distr(rgen);
        }

        while (solution.at(from).empty()) {
            from = distr(rgen);
        }

        distr = std::uniform_int_distribution<int>(0, solution.at(from).size() - 1);
        int a = distr(rgen);

        solution.at(to).push_back(solution.at(from)[a]);
        solution.at(from).erase(solution.at(from).begin() + a);

        return solution;
    }

    std::ostream &operator<<(std::ostream &o, const mhe::solution_t s) {
        for (int i = 0; i < 3; i++) {
            o << "S" << i + 1 << "= { ";
            for (auto e: s[i]) {
                o << e << " ";
            }
            o << "}" << std::endl;
        }
        o << "goal = " << s.goal() << std::endl << "--------------------------------------------" << std::endl;

        return o;
    }
} // mhe