#pragma once

#include "Solution.h"

class BruteForceSolution
{
public:
	BruteForceSolution();
	~BruteForceSolution();
	Solution loadSolution(vector<City>);
	vector<vector<City>> loadCitiesPermutation(vector<City>, vector<vector<City>>, int, int);
	vector<vector<City>> loadCitiesPermutation(vector<City>);
};

