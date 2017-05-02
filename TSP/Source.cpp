#include <iostream>
#include <fstream>
#include <vector>

#include "City.h"

using namespace std;

vector<City> getCitiesFromFile();

int main() {
	try {
		vector<City> cities = getCitiesFromFile();
		for (size_t i = 0; i < cities.size(); i++) {
			cout << "city " << i << ": (" << cities.at(i).getX() << ","
				<< cities.at(i).getY() << ")" << endl;
		}

	}
	catch (runtime_error & e) {
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}


vector<City> getCitiesFromFile() {
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
	while (file >> x >> y) {
		if (x < 0 || x > 1000) {
			throw runtime_error("Value of x must be between 0 and 1000");
		}
		if (y < 0 || y > 1000) {
			throw runtime_error("Value of y must be between 0 and 1000");
		}
		cities.push_back(City(x, y));
	}

	if (n != cities.size()) {
		throw runtime_error(
			"Quantity of cities informed different from number of cities listed");
	}

	file.close();

	return cities;
}