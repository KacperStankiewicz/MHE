#include <iostream>
#include <vector>
#include <numeric>
#include "solution_t.h"
#include "hillClimb.h"

std::random_device rd;
std::mt19937 rgen(rd());
//std::mt19937 rgen(1234567890);

using namespace mhe;

//todo: refactor this to use solution_t type
bool doesSubsetExist(std::vector<int> const &S, int n, int a, int b, int c, std::vector<int> &arr) {
    if (a == 0 && b == 0 && c == 0) {
        return true;
    }

    if (n < 0) {
        return false;
    }

    bool A = false;
    if (a - S[n] >= 0) {
        arr[n] = 1;
        A = doesSubsetExist(S, n - 1, a - S[n], b, c, arr);
    }

    bool B = false;
    if (!A && (b - S[n] >= 0)) {
        arr[n] = 2;
        B = doesSubsetExist(S, n - 1, a, b - S[n], c, arr);
    }

    bool C = false;
    if ((!A && !B) && (c - S[n] >= 0)) {
        arr[n] = 3;
        C = doesSubsetExist(S, n - 1, a, b, c - S[n], arr);
    }

    return A || B || C;
}

void partition(std::vector<int> const &S) {
    int setSum = accumulate(S.begin(), S.end(), 0);

    int numOfElements = S.size();

    std::vector<int> arr(numOfElements);

    bool result = (numOfElements >= 3) && !(setSum % 3) &&
                  doesSubsetExist(S, numOfElements - 1, setSum / 3, setSum / 3, setSum / 3, arr);

    if (!result) {
        std::cout << "3-Partition of set is not possible";
        return;
    }

    for (int i = 0; i < 3; i++) {
        std::cout << "Partition " << i << " is ";
        for (int j = 0; j < numOfElements; j++) {
            if (arr[j] == i + 1) {
                std::cout << S[j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    using namespace std;
//    std::vector<int> problem = mhe::generateProblem(30, 1, 100, rgen);
//    std::cout << problem << " sum: " <<std::accumulate(problem.begin(), problem.end(), 0) << std::endl;
//    for(int i=0 ; i< 10 ; i++){
//        std::cout << problem << std::accumulate(problem.begin(), problem.end(), 0) << std::endl;
//        partition(problem);
//        std::vector<int> problem = mhe::generateProblem(15, 1, 10, rgen);
//    }

//    std::vector<int> S = {7, 3, 2, 1, 5, 4, 8};
    problem_t problem = generateProblem(100, 1, 100, rgen);
//    std::vector<int> S;
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < problem.at(i).size(); j++){
//            S.push_back(problem[i][j]);
//        }
//    }

//    problem.at(0) = {1, 2};
//    problem.at(1) = {3, 4};
//    problem.at(2) = {5};

    solution_t solution = solution_t::forProblem(problem);
    cout << solution << endl;
    solution_t hillClimbSolution = randomHillClimb(solution, 100, rgen);

//    cout << solution.goal_sum;
//    solution.goal_sum = 5;
//    solution.problem->at(0) = {2, 3};
//    solution.problem->at(1) = {4, 1};
//    solution.problem->at(2) = {5, -15};
//    std::cout << solution << std::endl;

//    partition(vector<int>{1,2,3,4,5});

    return 0;
}