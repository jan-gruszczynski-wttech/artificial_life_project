//
// Created by jan.gruszczynski on 11.04.2023.
//

#ifndef ARTIFICIAL_LIFE_TABUSEARCH_H
#define ARTIFICIAL_LIFE_TABUSEARCH_H

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "utils.h"

using namespace std;


tuple<vector<int>, int, int, int> tabuSearchTSP(int numIterations, int tabuListSize, Instance *instance);

RESULT::Result TabuSearchEval(Instance *instance);

#endif //ARTIFICIAL_LIFE_TABUSEARCH_H
