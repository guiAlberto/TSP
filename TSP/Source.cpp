#include <iostream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <sstream>

#include "City.h"
#include "Solution.h"
#include "Util.h"
#include "BruteForceSolution.h"
#include "BranchAndBoundSolution.h"
#include "GeneticSolution.h"

using namespace std;

int main() {
	try {
		std::clock_t start;
		double duration;
		//vector<City> cities = Util().loadCitiesFromFile();
		for (size_t i = 0; i < 10; i++) {
			ostringstream ss;
			ss << i + 1;
			string fileName = "case" + ss.str() + ".txt";
			vector<City> cities = Util().loadCitiesFromFile(fileName);

			start = std::clock();
			Solution bruteForceSolution = BruteForceSolution().loadSolution(cities);
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "Time of Brute Force Solution with " << cities.size() << " vertices: " << duration << endl;
			Util().generateFileResult("Brute Force Solution", bruteForceSolution);

			start = std::clock();
			Solution brachAndBoundSolution = BranchAndBoundSolution().loadSolution(cities);
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "Time of Branch and Bound Solution with " << cities.size() << " vertices: " << duration << endl;
			Util().generateFileResult("Branch and Bound Solution", brachAndBoundSolution);

			start = std::clock();
			Solution geneticSolution = GeneticSolution().loadSolution(cities);
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			cout << "Time of Genetic Solution with " << cities.size() << " vertices: " << duration << endl;
			Util().generateFileResult("Genetic Solution", geneticSolution);
			cout << endl;
		}

		//Util().generateFileResult("Genetic Solution", geneticSolution);

	}
	catch (runtime_error & e) {
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}
