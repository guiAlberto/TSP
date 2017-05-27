#include <iostream>
#include <vector>

#include "City.h"
#include "Solution.h"
#include "Util.h"
#include "BruteForceSolution.h"
#include "BranchAndBoundSolution.h"

using namespace std;

int main() {
	try {
		vector<City> cities = Util().loadCitiesFromFile();
		
		Solution bruteForceSolution = BruteForceSolution().loadSolution(cities);
		Util().generateFileResult("Brute Force Solution", bruteForceSolution);

		Solution brachAndBoundSolution = BranchAndBoundSolution().loadSolution(cities);
		Util().generateFileResult("Branch and Bound Solution", brachAndBoundSolution);

	}
	catch (runtime_error & e) {
		cerr << e.what() << endl;
	}
	return 0;
}
