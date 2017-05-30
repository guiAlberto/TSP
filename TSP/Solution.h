#pragma once
#include <vector>
#include "City.h"

using namespace std;

class Solution
{
private:
	vector<City> cities;
	double distance;
	double time;
public:
	Solution();
	Solution(vector<City>, double, double);
	~Solution();

	vector<City> getCities();
	double getDistance();
	double getTime();

	void setCities(vector<City>);
	void setDistance(double);
	void setTime(double);
};
