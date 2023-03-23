#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include "Instance.h"

using namespace std;


void printVector(vector<int> &myVector) {
    for (auto y: myVector) { // Copy of 'x', almost always undesirable
        cout << y << " ";
    }
    cout << "\n";
}

vector<int> permutateList(vector<int> list_to_permutate) {
    auto vector_len = list_to_permutate.size();
    for (auto i = vector_len; i > 0; i--) {
        int rand_val = rand() % i;
        swap(list_to_permutate[i - 1], list_to_permutate[rand_val]);
    }
    return list_to_permutate;
}

vector<int> generateRandomSolution() {
    vector<int> solution(10);
    iota(solution.begin(), solution.end(), 0);
    auto permutatedSolution = permutateList(solution);
    return permutatedSolution;
}


vector<int> generateRandomWalkSolution(){
    vector<int> solution(10);
    iota(solution.begin(), solution.end(), 0);
    int rand_val = rand();
    cout<< rand_val<<"\n";
//    for (auto i = 10; i> 0)
    return solution;
}

int calculateSolutionCost(vector<int> &solution, Instance *instance) {
    printVector(solution);
    int cost = 0;
    for (auto x = 0; x < solution.size(); x++) {
        if ((x + 1) == solution.size()) {
            break;
        }
        cost = cost + instance->edge_weight(solution[x], solution[x + 1]);
//        cout << solution[x] << " " << solution[x + 1];
//        cout << "\n";
    }
    cost = cost + instance->edge_weight(solution[0], solution[solution.size()-1]);
    cout<<cost<<"\n";
    return cost;
}


int main() {
    srand(time(nullptr));

    std::cout << "Hello, World!" << std::endl;
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
    Instance *instance;
    instance = new Instance("rd100.tsp", true);
//    auto solution = generateRandomSolution();
    auto solution = generateRandomWalkSolution();
    calculateSolutionCost(solution, instance);


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
