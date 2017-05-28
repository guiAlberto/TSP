#include <iostream>
#include <vector>

#include "City.h"
#include "Solution.h"
#include "Util.h"
#include "BruteForceSolution.h"
#include "BranchAndBoundSolution.h"
#include "GeneticSolution.h"

using namespace std;

int main() {
	try {
		vector<City> cities = Util().loadCitiesFromFile();

		//Solution bruteForceSolution = BruteForceSolution().loadSolution(cities);
		//Util().generateFileResult("Brute Force Solution", bruteForceSolution);

		//Solution brachAndBoundSolution = BranchAndBoundSolution().loadSolution(cities);
		//Util().generateFileResult("Branch and Bound Solution", brachAndBoundSolution);

		Solution geneticSolution = GeneticSolution().loadSolution(cities);
		Util().generateFileResult("Genetic Solution", geneticSolution);

	}
	catch (runtime_error & e) {
		cerr << e.what() << endl;
	}
	return 0;
}
