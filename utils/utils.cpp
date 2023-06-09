//
// Created by Kapa on 02.04.2023.
//

#include "utils.h"

namespace mhe {

    std::ostream &operator<<(std::ostream &o, const std::vector<int> v) {
        o << " { ";
        for (auto e: v)
            o << e << " ";
        o << "}" << std::endl;
        return o;
    }

} // mhe