#include <iostream>
#include <vector>
#include <numeric>
#include "problemGenerator.h"
#include "solution_t.h"

std::mt19937 rgen(1234567890);

using namespace mhe;

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

//    std::vector<int> problem = mhe::generateProblem(7, 1, 9, rgen);
//    std::cout << problem << std::endl;
//    std::vector<int> S = {7, 3, 2, 1, 5, 4, 8};
    solution_t solution;
    solution.goal_sum = 10;
    solution.problem = {1, 2, 3, 4};
    solution.subsetA = {1};
    solution.subsetB = {2, 3};
    solution.subsetC = {4};
    std::cout << solution.goal() << std::endl;

//    partition(problem);

    return 0;
}