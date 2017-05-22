#pragma once
#include <vector>
#include "City.h"

using namespace std;

class Solution
{
private:
	vector<City> cities;
	double distance;
public:
	Solution();
	Solution(vector<City>, double);
	~Solution();

	vector<City> getCities();
	double getDistance();

	void setCities(vector<City> cities);
	void setDistance(double distance);
};
