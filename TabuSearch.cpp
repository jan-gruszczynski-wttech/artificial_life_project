//
// Created by jan.gruszczynski on 11.04.2023.
//

#include "TabuSearch.h"
#include "LocalSearch.h"

tuple<vector<int>, int, int, int> tabuSearchTSP(Instance *instance) {
    vector<int> currentSolution(instance->size);
    auto [solution, _a, _b, _c] = greedyLocalSearch(instance);
    currentSolution = solution;
    vector<int> bestSolution = currentSolution;
    int bestSolutionCost = calculateSolutionCost(bestSolution, instance);
    int startingSolutionCost = bestSolutionCost;
    vector<vector<int>> tabuList(instance->size, vector<int>(instance->size, 0));

    int numSteps = 0;
    int numEval = 0;
    int tabuTenure = instance->size / 4;
    int noImprovment = 0;
    while (true) {
        numSteps++;
        vector<int> candidateSolution = currentSolution;
        int city1, city2;
        int bestCandidateCost = numeric_limits<int>::max();

        for (int x = 0; x < instance->size - 1; x++) {
            for (int y = x + 1; y < instance->size; y++) {

                if (tabuList[currentSolution[x]][currentSolution[y]] == 0) {
                    numEval++;

                    swap(candidateSolution[x], candidateSolution[y]);
                    int candidateDistance = calculateSolutionCost(candidateSolution, instance);
                    if (candidateDistance < bestCandidateCost) {
                        bestCandidateCost = candidateDistance;
                        city1 = x;
                        city2 = y;
                    }
                    swap(candidateSolution[x], candidateSolution[y]);

                }
            }
        }

        for (int i = 0; i < instance->size; i++) {
            for (int j = 0; j < instance->size; j++) {
                if (tabuList[i][j] > 0) {
                    tabuList[i][j]--;
                }
            }
        }

        swap(currentSolution[city1], currentSolution[city2]);

        tabuList[currentSolution[city1]][currentSolution[city2]] = tabuList[currentSolution[city2]][currentSolution[city1]] = tabuTenure;

        int currentSolutionCost = calculateSolutionCost(currentSolution, instance);
        if (currentSolutionCost < bestSolutionCost) {
            bestSolution = currentSolution;
            bestSolutionCost = currentSolutionCost;
            noImprovment = 0;
        } else {
            noImprovment++;
        }

        if (noImprovment > 75) {
            break;
        }
    }

    return {bestSolution, numSteps, startingSolutionCost, numEval};
}

RESULT::Result TabuSearchEval(Instance *instance) {
    chrono::duration<double> deltaT{};
    auto t0 = chrono::high_resolution_clock::now();
    auto [randomSolution, numSteps, startingCost, numEval] = tabuSearchTSP(instance);
    deltaT = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - t0);
    int solutionCost = calculateSolutionCost(randomSolution, instance);
    return RESULT::Result{numSteps, solutionCost, deltaT, instance->fileName,
                          "TabuSearch", 0, randomSolution,
                          solutionCost, numEval};
}
