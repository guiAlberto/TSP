#pragma once

#include <vector>
#include "City.h"

using namespace std;

class Branch
{
private:
	vector<City> cities;
	double cost;

	void increaseCost(double);
public:
	Branch();
	Branch(vector<City>, double);
	~Branch();

	vector<City> getCities();
	double getCost();

	void setCities(vector<City>);
	void setCost(double);
	
	void putCity(City);
	bool equals(Branch);
	size_t size();
	void popCity();
};

