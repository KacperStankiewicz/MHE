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

        solution_t currentSolution = *this;
        while (from == to) {
            to = distr(rgen);
        }

        while (currentSolution.at(from).empty()) {
            from = distr(rgen);
        }

        distr = std::uniform_int_distribution<int>(0, currentSolution.at(from).size() - 1);
        int a = distr(rgen);

        currentSolution.at(to).push_back(currentSolution.at(from)[a]);
        currentSolution.at(from).erase(currentSolution.at(from).begin() + a);

        return currentSolution;
    }

    std::vector<solution_t> solution_t::findNeighbours() const {
        solution_t currentSolution = *this;
        std::vector<solution_t> neighbours;
        for (int i = 0; i < currentSolution.size(); i++) { // size = 3
            for (int j = 0; j < currentSolution[i].size(); j++) { // size of subset
                solution_t neighbour = currentSolution;
                neighbour[(i + 1) % 3].push_back(neighbour[i][j]);
                neighbour[i].erase(neighbour[i].begin() + j);
                neighbours.push_back(neighbour);
            }
        }
        return neighbours;
    }

    solution_t solution_t::bestNeighbour() const {
        solution_t solution = *this;
        std::vector<solution_t> neighbours = solution.findNeighbours();
        solution_t best = neighbours[0];

        for (auto x: neighbours) {
            if (x.goal() < best.goal()) {
                best = x;
            }
        }

        return best;
    }

    std::ostream &operator<<(std::ostream &o, const mhe::solution_t s) {
        for (int i = 0; i < 3; i++) {
            o << "S" << i + 1 << s[i];
//            "= { ";
//            for (auto e: s[i]) {
//                o << e << " ";
//            }
//            o << "}" << std::endl;
        }
        o << "goal = " << s.goal() << std::endl << "--------------------------------------------" << std::endl;

        return o;
    }
} // mhe