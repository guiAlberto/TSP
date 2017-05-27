#pragma once

#include <vector>
#include "City.h"

using namespace std;

class Path
{
private:
	vector<City> cities;
	double cost;

	void increaseCost(double);
public:
	Path();
	Path(vector<City>, double);
	~Path();

	vector<City> getCities();
	double getCost();

	void setCities(vector<City>);
	void setCost(double);
	
	void putCity(City);
	bool equals(Path);
	size_t size();
	void popCity();
};

