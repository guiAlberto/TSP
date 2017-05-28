#pragma once

#include <vector>
#include "City.h"

using namespace std;

class Chromosome
{
private:
	vector<City> cities;
	double cost;
public:
	Chromosome();
	Chromosome(vector<City>, double);
	~Chromosome();

	vector<City> getCities();
	double getCost();

	void setCities(vector<City>);
	void setCost(double);

	bool equals(Chromosome);
	
	bool isGoingToMutate(double);
	void popCity();
};
