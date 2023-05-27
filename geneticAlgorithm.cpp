//
// Created by Kapa on 13.05.2023.
//

#include <iostream>
#include "geneticAlgorithm.h"

namespace mhe {

    bool iterationEndCondition(threePartitionProblemGaConfig &config) {
        config.iteration++;
        return config.iteration <= config.maxIterations;
    }

    bool qualityEndCondition(std::vector<long> &fitnesses, threePartitionProblemGaConfig &config) {
        if (fitnesses.empty()) {
            return true;
        }

        for (auto x: fitnesses) {
            if (x >= config.targetQuality) {
                return false;
            }
        }
        return true;
    }

    std::vector<solution_t> getInitialPopulation(threePartitionProblemGaConfig config, std::mt19937 &rgen) {
        std::vector<solution_t> population;
        for (int i = 0; i < config.populationSize; i++) {
            population.push_back(solution_t::forProblem(config.problem).randomModify(rgen));
        }
        return population;
    }

    double fitness(solution_t solution) {
        return 1.0 / (1 + solution.goal());
    }

    std::vector<solution_t>
    tournamentSelection(std::vector<double> fitnesses, std::vector<solution_t> population, std::mt19937 &rgen) {
        std::vector<solution_t> selectedPopulation;
        while (selectedPopulation.size() < population.size()) {
            std::uniform_int_distribution<int> dist(0, population.size() - 1);
            int indexA = dist(rgen);
            int indexB = dist(rgen);
            if (fitnesses[indexA] >= fitnesses[indexB]) {
                selectedPopulation.push_back(population[indexA]);
            } else {
                selectedPopulation.push_back(population[indexB]);
            }
        }
        return selectedPopulation;
    }

    std::vector<solution_t>
    rouletteWheelSelection(std::vector<double> fitnesses, std::vector<solution_t> population, std::mt19937 &rgen) {
        std::vector<solution_t> selectedPopulation;

        double fitnessSum = 0.0;
        for (double fitness: fitnesses) {
            fitnessSum += fitness;
        }

        std::uniform_real_distribution<double> dist(0.0, fitnessSum);

        while (selectedPopulation.size() < population.size()) {
            double rouletteSpin = dist(rgen);
            double partialSum = 0.0;

            for (size_t i = 0; i < population.size(); i++) {
                partialSum += fitnesses[i];
                if (partialSum >= rouletteSpin) {
                    selectedPopulation.push_back(population[i]);
                    break;
                }
            }
        }

        return selectedPopulation;
    }

    std::pair<solution_t, solution_t> uniformCrossover(solution_t a, solution_t b, std::mt19937 &rgen) {
        std::uniform_int_distribution<int> distr(0, 1);

        for (int i = 0; i < 3; i++) {
            const int size = std::min(a[i].size(), b[i].size());
            for (int j = 0; j < size; j++) {
                if (distr(rgen)) {
                    std::swap(a[i][j], b[i][j]);
                }
            }
        }

        return {a, b};
    }

    std::pair<solution_t, solution_t> onePointCrossover(solution_t a, solution_t b, std::mt19937 &rgen) {
        int accumulativeSize = std::min(
                std::accumulate(a.begin(), a.end(), 0, [](auto l, auto r) {
                    return l + r.size();
                }),
                std::accumulate(b.begin(), b.end(), 0, [](auto l, auto r) {
                    return l + r.size();
                })
        );

        std::uniform_int_distribution<int> distr(1, accumulativeSize - 1);
        int point = distr(rgen);
        int counter = 0;
        for (int i = 0; i < 3; i++) {
            const int size = std::min(a[i].size(), b[i].size());
            for (int j = 0; j < size; j++) {
                if (counter > point) {
                    std::swap(a[i][j], b[i][j]);
                }
                counter++;
            }
        }

        return {a, b};
    }

    std::vector<solution_t> crossover(std::vector<solution_t> population, std::mt19937 &rgen) {
        std::vector<solution_t> offspring;
        for (int i = 0; i < population.size(); i += 2) {
            auto [a, b] = uniformCrossover(population.at(i), population.at(i + 1), rgen);
            offspring.push_back(a);
            offspring.push_back(b);
        }
        return offspring;
    }

    std::vector<solution_t> mutation(std::vector<solution_t> population, std::mt19937 &rgen) {
        std::vector<solution_t> mutatedPopulation;
        for (auto solution: population) {
            std::bernoulli_distribution bernoulliDistr(0.01);
            if (bernoulliDistr(rgen)) {
                solution = solution.randomModify(rgen);
            }
            mutatedPopulation.push_back(solution);
        }
        return mutatedPopulation;
    }

    std::vector<solution_t> leastElementsMutation(std::vector<solution_t> population, std::mt19937 &rgen) {
        std::vector<solution_t> mutatedPopulation(population.size());

        for (auto solution: population) {
            std::bernoulli_distribution bernoulliDistr(0.01);
            if (bernoulliDistr(rgen)) {
                std::uniform_int_distribution<int> distr(0, 2);
                int from = distr(rgen);
                int to = distr(rgen);
                while (from == to) {
                    to = distr(rgen);
                }
                while (solution.at(from).empty()) {
                    from = distr(rgen);
                }

                distr = std::uniform_int_distribution<int>(0, solution.at(from).size() - 1);
                int a = distr(rgen);

                auto minSizeIterator = std::min_element(solution.begin(), solution.end(),
                                                        [](const std::vector<int> &a, const std::vector<int> &b) {
                                                            return a.size() < b.size();
                                                        });

                solution.at(std::distance(solution.begin(), minSizeIterator)).push_back(solution.at(from)[a]);
                solution.at(from).erase(solution.at(from).begin() + a);
            }
            mutatedPopulation.push_back(solution);
        }
        return mutatedPopulation;
    }

    solution_t geneticAlgorithm(threePartitionProblemGaConfig &config, std::mt19937 &rgen) {
        auto population = getInitialPopulation(config, rgen);

        while (iterationEndCondition(config)) {
            std::vector<double> fitnesses;
            for (auto i: population) {
                fitnesses.push_back(fitness(i));
            }

            if (config.iteration % 500 == 0) {
                std::cout << "\niteration " << config.iteration << " fitnesses: " << std::endl;
                for (auto e: fitnesses) {
                    std::cout << e << " ";
                }
            }
            auto parents = tournamentSelection(fitnesses, population, rgen);
            auto offspring = crossover(parents, rgen);
            offspring = mutation(offspring, rgen);
            population = offspring;
        }
        return *std::max_element(population.begin(), population.end(),
                                 [&](auto l, auto r) { return fitness(l) > fitness(r); });
    }
} // mhe