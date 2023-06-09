//
// Created by Kapa on 06.05.2023.
//

#include <set>
#include <iostream>
#include <list>
#include "tabuSearch.h"

namespace mhe {

    solution_t tabuSearch(const solution_t &solution, int numOfIterations, int tabuSize) {
        std::set<solution_t> tabuSet;
        std::list<solution_t> previousSolutions;

        tabuSet.insert(solution);
        previousSolutions.push_back(solution);
        solution_t globalBest = solution;

        for (int i = 0; i < numOfIterations; i++) {
            std::vector<solution_t> neighbours = previousSolutions.back().findNeighbours();

            neighbours.erase(std::remove_if(neighbours.begin(),
                                            neighbours.end(),
                                            [&](solution_t s) {
                                                return tabuSet.contains(s);
                                            }),
                             neighbours.end());

            if (neighbours.empty()) {
                if (previousSolutions.size() == 1) {
                    std::cout << "Ate my tail..." << std::endl;
                    return globalBest;
                }
                previousSolutions.pop_back();
                continue;
            }

            solution_t nextSolution = neighbours.at(0);
            for (auto neighbour: neighbours) {
                if (nextSolution.goal() > neighbour.goal()) {
                    nextSolution = neighbour;
                }
            }

            if (nextSolution.goal() <= globalBest.goal()) {
                globalBest = nextSolution;
                std::cout << "TABU SEARCH\n" << "iteration: " << i << std::endl << globalBest;

                if (globalBest.goal() == 0) {
                    return globalBest;
                }

            }

            tabuSet.insert(nextSolution);
            if (tabuSet.size() > tabuSize && tabuSize > 0) { // unlimited tabu when tabuSize = 0
                tabuSet.erase(tabuSet.begin());
            }

            previousSolutions.push_back(nextSolution);
        }

        return globalBest;
    }
} // mhe