#include <iostream>
#include <vector>

#include "City.h"
#include "Solution.h"
#include "Util.h"
#include "BruteForceSolution.h"

using namespace std;

int main() {
	try {
		vector<City> cities = Util().loadCitiesFromFile();
		
		Solution loadSolution = BruteForceSolution().loadSolution(cities);
		Util().generateFileResult("Brute Force Solution", loadSolution);

	}
	catch (runtime_error & e) {
		cerr << e.what() << endl;
	}
	return 0;
}
