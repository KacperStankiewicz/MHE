#include <iostream>
#include <vector>
#include <numeric>
#include <ctime>
#include "utils/tp_args.hpp"
#include "solution/solution_t.h"
#include "hillclimb/hillClimb.h"
#include "tabu/tabuSearch.h"
#include "simulatedannealing/simulatedAnnealing.h"
#include "geneticalgorithm/threePartitionProblemGaConfig.h"
#include "geneticalgorithm/geneticAlgorithm.h"
#include <fstream>
#include <sstream>
#include <cstring>

std::random_device rd;
std::mt19937 rgen(rd());
//std::mt19937 rgen(1234567890);

using namespace mhe;

int main(int argc, char **argv) {
    using namespace std;
    using namespace tp::args;

    auto method = arg(argc,
                      argv,
                      "alg",
                      std::string("hillClimbRandom"),
                      "Available algorithms: (default: hillClimbRandom)\n"
                      "\t\t\t1. hillClimbRandom \n"
                      "\t\t\t2. hillClimbDeter \n"
                      "\t\t\t3. tabuSearch \n"
                      "\t\t\t4. simmAnnealing \n"
                      "\t\t\t5. geneticAlgorithm");

    auto tabuSize = arg(argc,
                        argv,
                        "tabuSize ",
                        50,
                        "Max tabu size. (if 0, then unlimited) (default: 50)");

    auto saTemperatureFunction = arg(argc,
                                     argv,
                                     "saTempFun ",
                                     std::string("n/k"),
                                     "Available temperature functions for Simulated Annealing Algorithm: (k - iteration number) (default: n/k) \n"
                                     "\t\t\t1. n/k \n"
                                     "\t\t\t2. n/log k");

    auto saTemperatureFunctionParameter = arg(argc,
                                              argv,
                                              "n ",
                                              1000.0,
                                              "N parameter value for SA temperature function (default: 1000.0)");

    auto crossoverMethod = arg(argc,
                               argv,
                               "crossover ",
                               std::string("uniform"),
                               "Available crossover methods: (default: uniform)\n"
                               "\t\t\t1. uniform \n"
                               "\t\t\t2. onePoint");

    auto mutationMethod = arg(argc,
                              argv,
                              "mutationMethod",
                              std::string("random"),
                              "Available mutationMethod methods: (default: random)\n"
                              "\t\t\t1. random \n"
                              "\t\t\t2. leastElements");

    auto endCondition = arg(argc,
                            argv,
                            "end",
                            std::string("iterations"),
                            "Available end conditions for GA: (default: iterations)\n"
                            "\t\t\t1. iterations\n "
                            "\t\t\t2. quality");

    auto quality = arg(argc,
                       argv,
                       "quality",
                       0.9,
                       "Percent value as decimal fraction (default: 0.9)");

    auto iterations = arg(argc,
                          argv,
                          "iter",
                          5040,
                          "Number of iterations (default: 5040)");

    auto selectionMethod = arg(argc,
                               argv,
                               "selection",
                               std::string("tournament"),
                               "Available end conditions: (default: tournament)\n"
                               "\t\t\t1. tournament \n"
                               "\t\t\t2. roulette ");

    auto populationSize = arg(argc,
                              argv,
                              "popSize",
                              10,
                              "Size of population for GA algorithm (default: 10)");

    auto problemSource = arg(argc,
                             argv,
                             "psource",
                             std::string("generator"),
                             "Available problem sources: (default: generator)\n"
                             "\t\t\t1. generator \n"
                             "\t\t\t2. file ");

    auto problemLength = arg(argc,
                             argv,
                             "plength",
                             50,
                             "Amount of numbers (default: 50)");

    auto problemMinValue = arg(argc,
                               argv,
                               "pmin",
                               1,
                               "Minimal value of generated numbers (default: 1)");

    auto problemMaxValue = arg(argc,
                               argv,
                               "pmax",
                               100,
                               "Max value of generated numbers (default: 100)");

    auto problemSourceFile = arg(argc,
                                 argv,
                                 "pfile",
                                 "data.txt",
                                 "Problem source filename (default: data.txt)");

    auto help = arg(argc,
                    argv,
                    "help",
                    false,
                    "Display available arguments");

    if (help) {
        std::cout << "\nHELP SCREEN\n" << std::endl;
        args_info(std::cout);
        return 0;
    }

    map<string, int> methodsMap = {
            {"hillClimbRandom",  0},
            {"hillClimbDeter",   1},
            {"tabuSearch",       2},
            {"simmAnnealing",    3},
            {"geneticAlgorithm", 4}
    };

    problem_t problem;
    solution_t solution;

    if (problemSource == "generator") {
        problem = generateProblem(problemLength, problemMinValue, problemMaxValue, rgen);
    } else {
        ifstream file;
        file.open(string(R"(D:\Studia\MHE\projekt\)") + problemSourceFile);
        if (file.is_open()) {
            std::string line;
            int vectorIndex = 0;

            while (std::getline(file, line)) {
                std::istringstream iss(line);
                int value;

                while (iss >> value) {
                    problem[vectorIndex].push_back(value);
                }

                vectorIndex = (vectorIndex + 1) % 3;
            }

            file.close();
        } else {
            cout << "File with given name not found... Using generated problem";
            problem = generateProblem(problemLength, problemMinValue, problemMaxValue, rgen);
        }
    }

    solution = solution_t::forProblem(problem);
    cout << "Starting solution: \n" << solution << endl;

    switch (methodsMap[method]) {
        case 0:
            solution = randomHillClimb(solution, iterations, rgen);
            cout << "Random hill climb solution: \n" << solution << endl;
            break;
        case 1:
            solution = deterministicHillClimb(solution, iterations);
            cout << "Deterministic hill climb solution: \n" << solution << endl;
            break;
        case 2:
            solution = tabuSearch(solution, iterations, tabuSize);
            cout << "Tabu search solution: \n" << solution << endl;
            break;
        case 3:
            if (saTemperatureFunction == "n/k") {
                solution = simulatedAnnealing(solution, [&saTemperatureFunctionParameter](int k) {
                    return saTemperatureFunctionParameter / k;
                }, iterations, rgen);
            } else {
                solution = simulatedAnnealing(solution, [&saTemperatureFunctionParameter](int k) {
                    return saTemperatureFunctionParameter / log(k);
                }, iterations, rgen);
            }
            cout << "Simulated annealing solution: \n" << solution << endl;
            break;
        case 4:
            threePartitionProblemGaConfig config(crossoverMethod,
                                                 mutationMethod,
                                                 selectionMethod,
                                                 endCondition,
                                                 iterations,
                                                 populationSize,
                                                 quality,
                                                 problem);

            solution = geneticAlgorithm(config, rgen);
            cout << "Genetic algorithm solution: \n" << solution << endl;
            break;
    }


//    problem_t problem = generateProblem(50, 1, 50, rgen);
//    solution_t solution = solution_t::forProblem(problem);
//    cout << "solution start: \n" << solution << endl;
//
//    solution_t randomHillClimbSolution = randomHillClimb(solution, 5040, rgen);
//    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
//    solution_t deterministicHillClimbSolution = deterministicHillClimb(solution, 5040);
//    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
//    solution_t tabuSearchSolution = tabuSearch(solution, 5040, 0);
//    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
//    solution_t simAnnealingSolution = simulatedAnnealing(solution, [](int k){return 1000.0/k;}, 5040, rgen);
//    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
//
//    threePartitionProblemGaConfig config(5040, 10, 0.9, problem);
//    solution_t geneticAlgorithm = mhe::geneticAlgorithm(config, rgen);



//    cout << "solution random: \n" << randomHillClimbSolution << endl;
//    cout << "solution deterministic: \n" << deterministicHillClimbSolution << endl;
//    cout << "solution tabu: \n" << tabuSearchSolution << endl;
//    cout << "solution annealing: \n" << simAnnealingSolution << endl;
//    cout << "solution GA: \n" << geneticAlgorithm << endl;

//    cout << solution.goal_sum;
//    solution.goal_sum = 5;
//    solution.problem->at(0) = {2, 3};
//    solution.problem->at(1) = {4, 1};
//    solution.problem->at(2) = {5, -15};
//    std::cout << solution << std::endl;

//    partition(vector<int>{1,2,3,4,5});

    return 0;
}