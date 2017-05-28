#include <random>

#include "Chromosome.h"
#include "Util.h"


bool Chromosome::isGoingToMutate(double chance)
{
	double  randomNumber = Util().loadRandomNumber(0, 100);
	return chance > randomNumber ? true : false;
}

void Chromosome::popCity()
{
	this->cities.pop_back();
}

Chromosome::Chromosome()
{
}

Chromosome::Chromosome(vector<City> cities, double cost)
{
	this->cities = cities;
	this->cost = cost;
}


Chromosome::~Chromosome()
{
}

vector<City> Chromosome::getCities()
{
	return this->cities;
}

double Chromosome::getCost()
{
	return this->cost;
}

void Chromosome::setCities(vector<City> cities)
{
	this->cities = cities;
}

void Chromosome::setCost(double cost)
{
	this->cost = cost;
}

bool Chromosome::equals(Chromosome chromosome)
{
	size_t pathSize = chromosome.getCities().size();
	size_t thisSize = this->cities.size();
	if (pathSize != thisSize) {
		return false;
	}

	for (size_t i = 0; i < this->cities.size(); i++) {
		if (this->cities.at(i).getId() != chromosome.getCities().at(i).getId()) {
			return false;
		}
	}
	return true;
}
