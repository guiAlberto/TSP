#include <fstream>
#include <random>
#include <sstream>

#include "Util.h"

Util::Util()
{
}


Util::~Util()
{
}


vector<City> Util::loadCitiesFromFile() {
	vector<City> cities;

	ifstream file("cities.txt");

	if (!file.is_open()) {
		throw new runtime_error("File not found");
	}

	size_t n;
	file >> n;

	if (n < 0 || n > 100) {
		throw runtime_error("Quantity of cities must be between 0 and 100");
	}

	int x, y;
	int id = 1;
	while (file >> x >> y) {
		if (x < 0 || x > 1000) {
			throw runtime_error("Value of x must be between 0 and 1000");
		}
		if (y < 0 || y > 1000) {
			throw runtime_error("Value of y must be between 0 and 1000");
		}
		cities.push_back(City(x, y, id));
		id++;
	}

	if (n != cities.size()) {
		throw runtime_error(
			"Quantity of cities informed different from number of cities listed");
	}

	file.close();

	return cities;
}

vector<City> Util::loadCitiesFromFile(int i)
{
	vector<City> cities;
	ostringstream ss;
	ss << i + 1;
	string fileName = "case" + ss.str() + ".txt";

	ifstream file(fileName);

	if (!file.is_open()) {
		throw new runtime_error("File not found");
	}

	size_t n;
	file >> n;

	if (n < 0 || n > 100) {
		throw runtime_error("Quantity of cities must be between 0 and 100");
	}

	int x, y;
	int id = 1;
	while (file >> x >> y) {
		if (x < 0 || x > 1000) {
			throw runtime_error("Value of x must be between 0 and 1000");
		}
		if (y < 0 || y > 1000) {
			throw runtime_error("Value of y must be between 0 and 1000");
		}
		cities.push_back(City(x, y, id));
		id++;
	}

	if (n != cities.size()) {
		throw runtime_error(
			"Quantity of cities informed different from number of cities listed");
	}

	file.close();

	return cities;
}

void Util::generateFileResult(string filename, Solution solution) {
	double distance = solution.getDistance();
	vector<City> cities = solution.getCities();

	ofstream file;
	file.open(filename + ".txt");
	file << solution.getDistance() << endl;
	for (size_t i = 0; i < cities.size(); i++) {
		file << cities.at(i).getId() << " ";
	}
	file << endl;
	file.close();
}


double Util::loadDistance(City a, City b) {
	double dx = pow((a.getX() - b.getX()), 2);
	double dy = pow((a.getY() - b.getY()), 2);
	double distance = sqrt(dx + dy);
	return distance;
}

double Util::loadRandomNumber(double min, double max)
{
	random_device rd;
	uniform_real_distribution<double> ud(min, max);
	mt19937 mt(rd());
	return ud(mt);
}

int Util::loadRandomNumber(int min, int max)
{
	random_device rd;
	uniform_int_distribution<int> ud(min, max);
	mt19937 mt(rd());
	return ud(mt);
}

clock_t Util::timer()
{
	clock_t now;
	now = clock();
	return now;
}


double Util::loadDistance(vector<City> cities) {
	double distance = 0;
	for (size_t i = 0; i < cities.size() - 1; i++) {
		distance += loadDistance(cities.at(i), cities.at(i + 1));
	}
	return distance;
}