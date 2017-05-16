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

	vector<City> getCities() {
		return this->cities;
	}

	double getDistance() {
		return this->distance;
	}

	void setCities(vector<City> cities) {
		this->cities = cities;
	}

	void setDistance(double distance) {
		this->distance = distance;
	}
};
