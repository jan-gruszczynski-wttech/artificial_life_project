#include <iostream>
#include <vector>
#include <chrono>
#include <iostream>
#include <array>
#include "utils.h"
#include "Instance.h"
#include "LocalSearch.h"
#include "RandomSolutions.h"
#include "GreedyHeuristic.h"
#include "TabuSearch.h"

//Following set of scripts were used to load data: https://github.com/Kotbenek/TSP Implemented by KotBenek.

double evalFunction(Instance *instance, ofstream &myFile, RESULT::Result (*func)(Instance *instance)) {
    vector<RESULT::Result> listOfResults;
    chrono::duration<double> deltaT{};
    int counter = 0;
    auto t0 = chrono::high_resolution_clock::now();
    long scores = 0;
    do {
        auto result = func(instance);

        listOfResults.push_back(result);

//        cout << "Obtained score:" << result.attainedScore << " Num steps: " << result.numSteps << endl;
//        cout << result.toString();

        counter++;
        scores = scores + result.attainedScore;
        deltaT = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - t0);
    } while ((deltaT < chrono::seconds{1000000}) && (counter < 200));
    cout << "Average score: " << scores / counter << endl;
    cout << "Instance name: " << listOfResults[0].instanceName << "Function name: " << listOfResults[0].functionName
         << endl;
    cout << "Average time elapsed: " << deltaT.count() / counter << endl;
    cout << endl;
    for (auto result: listOfResults) {
        result.averageTimeElapsed = deltaT.count() / counter;
        myFile << result.toString();
    }
    return deltaT.count() / counter;
}


int main() {

    const char *instances[8] = {"eil51.tsp", "st70.tsp", "eil76.tsp", "rd100.tsp", "pr107.tsp",
                                "bier127.tsp", "pr136.tsp", "ch150.tsp"};
//    const char *instances[2] = {"rd100.tsp", "pr136.tsp",};

//    Instance *instance;
//    instance = new Instance("burma14.tsp", true);
//    instance = new Instance("burma14.tsp", true);

    ofstream myFile;
    myFile.open("Results200_final_all.txt");
    myFile
            << "numSteps;score;time;instanceName;functionName;AverageTimeElapsed;startingScore;numEvaluation;FinalSolution\n";
    for (auto instancePath: instances) {
        Instance *instance;
        instance = new Instance(instancePath, true);
        evalFunction(instance, myFile, &simulatedAnnealingEval);
        evalFunction(instance, myFile, &TabuSearchEval);
        evalFunction(instance, myFile, &generateRandomSolutionEval);
        evalFunction(instance, myFile, &generateRandomWalkSolutionEval);
        evalFunction(instance, myFile, &generateGreedyHeuristicSolutionEval);
        evalFunction(instance, myFile, &localSearchEval);
        evalFunction(instance, myFile, &greedyLocalSearchEval);
        cout << endl;
//        break;
    }

    myFile.close();





//    // TABU SEARCH:
//    Instance *instance;
//    instance = new Instance("rd100.tsp", true);
//    int numIterations = 50;
//    int tabuListSize = 100;
//
//    // Run Tabu Search for the TSP problem
//    vector<int> bestTour = tabuSearchTSP(numIterations, tabuListSize, instance);
//
//    // Print the best tour found
//    cout << "Best tour: ";
//    for (int city: bestTour) {
//        cout << city << " -> ";
//    }
//    cout << bestTour[0] << endl;
//
//    // Print the total distance of the best tour
////    double bestTourDistance = calculateDistance(distanceMatrix, bestTour);
//    double bestTourDistance = calculateSolutionCost(bestTour, instance);
//    cout << "Total distance: " << bestTourDistance << endl;
////----------------------------



//    cout<<randomFloat();
//    Instance *instance;
//    instance = new Instance("rd100.tsp", true);
////    auto [randomSolution, startingScore, numSteps] = generateRandomSolution(instance);
//    auto [randomSolution, startingScore, numSteps] = simulatedAnnealing(instance);
//    cout << printVector(randomSolution);
//    cout << endl << "Score " << calculateSolutionCost(randomSolution, instance);
//



//    const char *instances[8] = { "eil51.tsp", "st70.tsp", "eil76.tsp", "rd100.tsp", "pr107.tsp",
//                                 "bier127.tsp", "pr136.tsp", "ch150.tsp"};
////    const char *instances[2] = {"bier127.tsp", "pr136.tsp",};
//
////    Instance *instance;
////    instance = new Instance("burma14.tsp", true);
////    instance = new Instance("burma14.tsp", true);
//
//    ofstream myFile;
//    myFile.open("results200_final.txt");
//    myFile << "numSteps;score;time;instanceName;functionName;AverageTimeElapsed;startingScore;numEvaluation;FinalSolution\n";
//    for (auto instancePath: instances) {
//        Instance *instance;
//        instance = new Instance(instancePath, true);
//
//        evalFunction(instance, myFile, &generateRandomSolutionEval);
//        evalFunction(instance, myFile, &generateRandomWalkSolutionEval);
//        evalFunction(instance, myFile, &generateGreedyHeuristicSolutionEval);
//        evalFunction(instance, myFile, &localSearchEval);
//        evalFunction(instance, myFile, &greedyLocalSearchEval);
//        cout << endl;
////        break;
//    }
//
//    myFile.close();







//    calculateSolutionCost(solution, instance);
//    instance.

//    auto solution3 = generateRandomWalkSolution(instance);
//    vector<int> solution = {1,2,3,4,5,6,7,8,9};
//    printVector(solution);
//    solution = edgeSwap(solution, 0, 4);
//    printVector(solution);


//    for (auto start = chrono::steady_clock::now(), now = start;
//         now < start + chrono::seconds{1}; now = chrono::steady_clock::now()) {
//
//        calculateSolutionCost(solution, instance);
//    }


//    unsigned long long amount = 2;
//    unsigned long long min = 0;
//    unsigned long long max = 99;
//    RandomIterator iterator(amount, min, max);
//    cout<< iterator.next()<<iterator.next();
//    srand(time(nullptr));
//    for (auto x = 0; x < 1000; x++) {
//        cout << generateRandomInt(1, 10) << endl;
//        vector<int> randomSolution = {1, 2, 3, 4, 5, 6};
//        randomSolution = permutateList(randomSolution);
//        printVector(randomSolution);
//    }




//    int mean = uniform_dist(e1);
//    cout<< mean<< endl;
//    std::cout << "Hello, World!" << std::endl;
//    srand(time(0));
//    int rand_val = rand() % 10;
//    cout<<rand_val;

//    int instanceSize = 100;
//
//    vector<int> solution(100);
//    iota(solution.begin(), solution.end(), 0);
//    for( auto y : solution) { // Copy of 'x', almost always undesirable
//        cout << y << " ";
//    };



//    printVector(randomSolution);


//    permutateList(solution);
//    Instance *instance;
//
//    instance = new Instance("rd100.tsp", true);
//    cout << instance->size;
//
//
//
//    for( auto y : instance. ) { // Copy of 'x', almost always undesirable
//        cout << y << " ";
//    }



    return 0;
}
