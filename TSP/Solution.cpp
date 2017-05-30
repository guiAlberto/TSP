#include "Solution.h"



Solution::Solution()
{
}


Solution::Solution(vector<City> cities, double distance, double time)
{
	this->cities = cities;
	this->distance = distance;
	this->time = time;
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

double Solution::getTime()
{
	return this->time;
}

void Solution::setCities(vector<City> cities)
{
	this->cities = cities;
}

void Solution::setDistance(double distance)
{
	this->distance = distance;
}

void Solution::setTime(double time)
{
	this->time = time;
}
