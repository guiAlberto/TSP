#include "Solution.h"



Solution::Solution()
{
}

Solution::Solution(vector<City> cities, double distance)
{
	this->cities = cities;
	this->distance = distance;
}

Solution::~Solution()
{
}

vector<City> Solution::getCities()
{
	return this->cities;
}

double Solution::getDistance()
{
	return this->distance;
}

void Solution::setCities(vector<City> cities)
{
	this->cities = cities;
}

void Solution::setDistance(double distance)
{
	this->distance = distance;
}
