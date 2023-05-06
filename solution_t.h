//
// Created by Kapa on 25.03.2023.
//

#ifndef PROJEKT_SOLUTION_T_H
#define PROJEKT_SOLUTION_T_H

#include <vector>
#include <memory>
#include "utils.h"
#include "problem_t.h"

namespace mhe {

    class solution_t : public std::array<std::vector<int>, 3> {
    public:
        std::shared_ptr<problem_t> problem;
        int goal_sum;

        static solution_t forProblem(problem_t problem_);

        int goal() const;

        solution_t randomModify(std::mt19937 &rgen) const;

        solution_t bestNeighbour() const;

        std::vector<solution_t> findNeighbours() const;
    };

    std::ostream &operator<<(std::ostream &o, mhe::solution_t s);

} // mhe

#endif //PROJEKT_SOLUTION_T_H
