#pragma once

#include <vector>
#include <ctime>

#include "City.h"
#include "Solution.h"

using namespace std;

class Util
{
public:
	Util();
	~Util();
	
	vector<City> loadCitiesFromFile();
	vector<City> loadCitiesFromFile(int);
	void generateFileResult(string, Solution);
	
	double loadDistance(vector<City>);
	double loadDistance(City, City);

	double loadRandomNumber(double, double);
	int loadRandomNumber(int, int);

	clock_t timer();
};

