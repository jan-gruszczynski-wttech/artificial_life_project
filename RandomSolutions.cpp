//
// Created by jan.gruszczynski on 26.03.2023.
//

#include "RandomSolutions.h"

tuple<vector<int>, int, int> generateRandomSolution(Instance *instance) {
    vector<int> solution(instance->size);
    iota(solution.begin(), solution.end(), 0);
    auto permutatedSolution = permutateList(solution);
    int solutionCost = calculateSolutionCost(permutatedSolution, instance);
    int startingCost = solutionCost;
    long numSteps = 0;
    for (auto start = chrono::steady_clock::now(), now = start;
         now < start + chrono::milliseconds{1000}; now = chrono::steady_clock::now()) {
        numSteps++;
        vector<int> newSolution(instance->size);
        iota(newSolution.begin(), newSolution.end(), 0);
        newSolution = permutateList(newSolution);
        int newCost = calculateSolutionCost(newSolution, instance);
        if (newCost < solutionCost) {
            solutionCost = newCost;
            permutatedSolution = newSolution;
        }

    }

    return {permutatedSolution, startingCost, numSteps};
}


double calculate_initial_temperature(vector<int> &solution, double acceptance_ratio, int num_iterations,
                                     Instance *instance) {
    int numAcceptedMoves = 0;
    double deltaSum = 0.0;

    unsigned long min = 0;
    unsigned long max = solution.size() - 1;
    for (int i = 0; i < num_iterations; ++i) {
        int *ints = generateTwoRandomInts(min, max);
        int city1 = ints[0];
        int city2 = ints[1];

        if (city1 == city2) {
            continue;
        }
        double currentDistance = calculateSolutionCost(solution, instance);
        swap(solution[city1], solution[city2]);
        double newSolutionCost = calculateSolutionCost(solution, instance);
        double delta = currentDistance - newSolutionCost;

        if (delta > 0) {
            numAcceptedMoves++;
            deltaSum += delta;
        } else {
            swap(solution[city1], solution[city2]);
        }
    }

    double meanDelta = deltaSum / numAcceptedMoves;
    double initial_temperature = -meanDelta / log(acceptance_ratio);
    return initial_temperature;
}


tuple<vector<int>, int, int> simulatedAnnealing(Instance *instance) {
    vector<int> solution(instance->size);
    iota(solution.begin(), solution.end(), 0);
    auto bestFoundSolution = permutateList(solution);
    int bestSolutionCost = calculateSolutionCost(bestFoundSolution, instance);
    int startingCost = bestSolutionCost;
    unsigned long min = 0;
    unsigned long max = bestFoundSolution.size() - 1;

    vector<int> newSolution(instance->size);
    int newSolutionCost;
    double T = calculate_initial_temperature(bestFoundSolution, 0.95, 1000, instance);

    double alpha = 0.9;
    long numSteps = 0;
    int epochLen = 10000;
    while (T > 0.01) {
        numSteps += 1;
        for (int i = 0; i < epochLen; i++) {
            int *ints = generateTwoRandomInts(min, max);
            int i1 = ints[0];
            int i2 = ints[1];
            newSolution = edgeSwap(bestFoundSolution, i1, i2);
            newSolutionCost = calculateSolutionCost(newSolution, instance);
            int delta = newSolutionCost - bestSolutionCost;
            if (delta < 0) {
                bestFoundSolution = newSolution;
                bestSolutionCost = newSolutionCost;
            } else {
                double p = randomFloat();
                if (p < exp(-delta / T)) {
                    bestFoundSolution = newSolution;
                    bestSolutionCost = newSolutionCost;
                }
            }
        }
        T = T * alpha;
    }
    return {bestFoundSolution, numSteps, startingCost};
}


RESULT::Result simulatedAnnealingEval(Instance *instance) {
    chrono::duration<double> deltaT{};
    auto t0 = chrono::high_resolution_clock::now();

    auto [randomSolution, numSteps, startingCost] = simulatedAnnealing(instance);

    deltaT = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - t0);
    int solutionCost = calculateSolutionCost(randomSolution, instance);
    return RESULT::Result{numSteps, solutionCost, deltaT, instance->fileName,
                          "SimulatedAnnealing", 0, randomSolution, startingCost, numSteps * 10000};
}


vector<int> generateRandomSolutionForLocalSearch(Instance *instance) {
    vector<int> solution(instance->size);
    iota(solution.begin(), solution.end(), 0);
    auto permutatedSolution = permutateList(solution);
    return permutatedSolution;
}

RESULT::Result generateRandomSolutionEval(Instance *instance) {
    chrono::duration<double> deltaT{};
    auto t0 = chrono::high_resolution_clock::now();
    auto [randomSolution, startingScore, numSteps] = generateRandomSolution(instance);
    deltaT = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - t0);
    int solutionCost = calculateSolutionCost(randomSolution, instance);
    return RESULT::Result{numSteps, solutionCost, deltaT, instance->fileName,
                          "randomSolution", 0, randomSolution, startingScore, numSteps};
}


tuple<vector<int>, long, int> generateRandomWalkSolution(Instance *instance) {
    auto startingSolution = generateRandomSolutionForLocalSearch(instance);
    long currentCost = calculateSolutionCost(startingSolution, instance);
    int startingCost = currentCost;
//    long startingCost = currentCost;
//    cout << "Starting solution cost: " << currentCost << endl;
    unsigned long min = 0;
    unsigned long max = startingSolution.size() - 1;
    long numSteps = 0;

    // https://stackoverflow.com/questions/45442963/how-to-execute-a-while-loop-for-exactly-60-seconds-in-c
    vector<int> nextSolution;
    for (auto start = chrono::steady_clock::now(), now = start;
         now < start + chrono::milliseconds{1000}; now = chrono::steady_clock::now()) {
        int *ints = generateTwoRandomInts(min, max);
        int i1 = ints[0];
        int i2 = ints[1];
        nextSolution = edgeSwap(startingSolution, i1, i2);
        long costOfNextSolution = calculateSolutionCost(nextSolution, instance);
        if (costOfNextSolution < currentCost) {
            startingSolution = nextSolution;
            currentCost = costOfNextSolution;
        }
        numSteps++;
    }
//    cout << "Current cost: " << currentCost << endl;
//    cout << "Gain: " << startingCost - currentCost << endl;
    return {startingSolution, numSteps, startingCost};
}

RESULT::Result generateRandomWalkSolutionEval(Instance *instance) {
    chrono::duration<double> deltaT{};
    auto t0 = chrono::high_resolution_clock::now();

    auto [randomSolution, numSteps, startingCost] = generateRandomWalkSolution(instance);

    deltaT = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - t0);
    int solutionCost = calculateSolutionCost(randomSolution, instance);
    return RESULT::Result{numSteps, solutionCost, deltaT, instance->fileName,
                          "randomWalk", 0, randomSolution, startingCost, numSteps};
}
