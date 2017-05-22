#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "City.h"
#include "Solution.h"

using namespace std;

vector<City> loadCitiesFromFile();
Solution loadBuruteForceSolution(vector<City>);
vector<vector<City>> loadCitiesPermutation(vector<City>);
vector<vector<City>> loadCitiesPermutation(vector<City>, vector<vector<City>>, int, int);
double loadDistance(vector<City>);
double loadDistance(City, City);
void generateFileResult(string, Solution);

int main() {
	try {
		vector<City> cities = loadCitiesFromFile();
		Solution bruteForceSolution = loadBuruteForceSolution(cities);
		generateFileResult("Brute Force Solution", bruteForceSolution);
	}
	catch (runtime_error & e) {
		cerr << e.what() << endl;
	}
	return 0;
}


vector<City> loadCitiesFromFile() {
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

Solution loadBuruteForceSolution(vector<City> cities) {
	int n = cities.size() - 1;
	vector<vector<City>> permutation = loadCitiesPermutation(cities);
	double bestDistance;
	vector<City> bestCities;
	int i = 0;
	for (size_t i = 0; i < permutation.size(); i++) {
		vector<City> citiesTemp = permutation.at(i);
		double distanceTemp = loadDistance(citiesTemp);
		if (i == 0) {
			bestDistance = distanceTemp;
			bestCities = citiesTemp;
		}
		else {
			if (distanceTemp < bestDistance) {
				bestDistance = distanceTemp;
				bestCities = citiesTemp;
			}
		}
		i++;
	}
	return Solution(bestCities, bestDistance);
}

vector<vector<City>> loadCitiesPermutation(vector<City> cities) {
	// resolution found in https://goo.gl/AqHmnS
	vector<vector<City>> permutation;
	int n = cities.size() - 1;
	permutation = loadCitiesPermutation(cities, permutation, 0, n);
	return permutation;
}

vector<vector<City>> loadCitiesPermutation(vector<City> cities, vector<vector<City>> permutation, int l, int r) {
	int i;
	if (l == r) {
		permutation.push_back(cities);
	}
	else {
		for (i = l; i <= r; i++) {
			swap(cities[l], cities[i]);
			permutation = loadCitiesPermutation(cities, permutation, l + 1, r);
			swap(cities[l], cities[i]);
		}
	}
	return permutation;
}

double loadDistance(vector<City> cities) {
	double distance = 0;
	for (size_t i = 0; i < cities.size() - 1; i++) {
		distance += loadDistance(cities.at(i), cities.at(i + 1));
	}
	distance += loadDistance(cities.front(), cities.back());
	return distance;
}

double loadDistance(City a, City b) {
	double dx = pow((a.getX() - b.getX()), 2);
	double dy = pow((a.getY() - b.getY()), 2);
	double distance = sqrt(dx + dy);
	return distance;
}

void generateFileResult(string filename, Solution solution) {
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
