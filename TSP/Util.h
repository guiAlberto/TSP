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
	
	double loadDistance(vector<City>);
	double loadDistance(City, City);

	double loadRandomNumber(double, double);
	int loadRandomNumber(int, int);
};

