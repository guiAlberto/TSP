#include "Path.h"
#include "Util.h"

void Path::putCity(City city)
{
	this->increaseCost(Util().loadDistance(this->cities.back(), city));
	this->cities.push_back(city);
}

void Path::increaseCost(double cost)
{
	this->cost += cost;
}

bool Path::equals(Path path)
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

size_t Path::size()
{
	return this->cities.size();
}

void Path::popCity()
{
	this->cities.pop_back();
}

Path::Path()
{
}

Path::Path(vector<City> cities, double cost)
{
	this->cities = cities;
	this->cost = cost;
}


Path::~Path()
{
}

vector<City> Path::getCities()
{
	return this->cities;
}

double Path::getCost()
{
	return this->cost;
}

void Path::setCities(vector<City> cities)
{
	this->cities = cities;
}

void Path::setCost(double cost)
{
	this->cost = cost;
}
