// Following set of scripts were used to load data: https://github.com/Kotbenek/TSP Implemented by KotBenek.
// Source: https://github.com/Kotbenek/TSP
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>

#include "StringFunctions.h"
#include "CoordsWeightType.h"

using namespace std;

class Instance
{
public:
	int size = -1;
	int64_t optimal_tour_length = -1;
	string fileName;
	Instance(string filename, bool parse_data_to_matrix);
	~Instance();
	int edge_weight(int from, int to);
	void display();
    int** matrix;
    int** matrix_copy;
    void resetCopyMatrix();
private:
	double** coords;
	CoordsWeightType coords_weight_type;
	bool is_instance_data_in_matrix;

	int nint(double d);
	double** parse_coords(vector<string> file, int i, int dimensions);
	int max(int i1, int i2);
	int max(int i1, int i2, int i3);
	void load_optimal_tour_length(string filename);

	int euc_2d_distance(int from_city, int to_city);
	int euc_3d_distance(int from_city, int to_city);
	int max_2d_distance(int from_city, int to_city);
	int max_3d_distance(int from_city, int to_city);
	int man_2d_distance(int from_city, int to_city);
	int man_3d_distance(int from_city, int to_city);
	int ceil_2d_distance(int from_city, int to_city);
	int geo_distance(int from_city, int to_city);
	int att_distance(int from_city, int to_city);


};