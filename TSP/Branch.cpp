#include "Branch.h"
#include "Util.h"

void Branch::putCity(City city)
{
	this->increaseCost(Util().loadDistance(this->cities.back(), city));
	this->cities.push_back(city);
}

void Branch::increaseCost(double cost)
{
	this->cost += cost;
}

bool Branch::equals(Branch path)
{
	size_t pathSize = path.getCities().size();
	size_t thisSize = this->cities.size();
	if (pathSize != thisSize) {
		return false;
	}

	for (size_t i = 0; i < this->cities.size(); i++) {
		if (this->cities.at(i).getId() != path.getCities().at(i).getId()) {
			return false;
		}
	}
	return true;
}

size_t Branch::size()
{
	return this->cities.size();
}

void Branch::popCity()
{
	this->cities.pop_back();
}

Branch::Branch()
{
}

Branch::Branch(vector<City> cities, double cost)
{
	this->cities = cities;
	this->cost = cost;
}


Branch::~Branch()
{
}

vector<City> Branch::getCities()
{
	return this->cities;
}

double Branch::getCost()
{
	return this->cost;
}

void Branch::setCities(vector<City> cities)
{
	this->cities = cities;
}

void Branch::setCost(double cost)
{
	this->cost = cost;
}
