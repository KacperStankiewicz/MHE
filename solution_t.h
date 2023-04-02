//
// Created by Kapa on 25.03.2023.
//

#ifndef PROJEKT_SOLUTION_T_H
#define PROJEKT_SOLUTION_T_H

#include <vector>

namespace mhe {

    class solution_t {
    public:
        std::vector<int> problem;
        int goal_sum;
        std::vector<int> subsetA;
        std::vector<int> subsetB;
        std::vector<int> subsetC;

        int goal() const;
    };

} // mhe

#endif //PROJEKT_SOLUTION_T_H
