#include "City.h"



bool City::equals(City city)
{
	if (city.getId() == this->id) {
		return true;
	}
	return false;
}

City::City(int x, int y, int id) {
	this->x = x;
	this->y = y;
	this->id = id;
}


City::~City()
{
}

int City::getX()
{
	return this->x;
}

int City::getY()
{
	return this->y;
}

int City::getId()
{
	return this->id;
}
