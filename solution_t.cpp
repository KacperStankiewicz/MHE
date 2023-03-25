//
// Created by Kapa on 25.03.2023.
//

#include <numeric>
#include "solution_t.h"

namespace mhe {
    int solution_t::goal() const {
        int difference = 0;
        difference += goal_sum - std::reduce(subsetA.begin(), subsetA.end());
        difference += goal_sum - std::reduce(subsetB.begin(), subsetB.end());
        difference += goal_sum - std::reduce(subsetC.begin(), subsetC.end());
        return difference;
    }
} // mhe