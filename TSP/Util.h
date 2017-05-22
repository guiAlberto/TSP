#pragma once

#include <vector>

#include "City.h"
#include "Solution.h"

using namespace std;

class Util
{
public:
	Util();
	~Util();
	vector<City> loadCitiesFromFile();
	void generateFileResult(string, Solution);
	double loadDistanceFromVector(vector<City>);
	double loadDistanceFromTwoCities(City, City);
};

