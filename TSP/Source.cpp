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
		//para pegar o exemplo na descrição do trabalho, use o método vector<City> loadCitiesFromFile(); fora do "for"
		for (size_t i = 0; i < 10; i++) {
			//para pegar os casos de testes, use o método vector<City> loadCitiesFromFile(int); dentro do "for"
			vector<City> cities = Util().loadCitiesFromFile(i);

			Solution bruteForceSolution = BruteForceSolution().loadSolution(cities);
			Util().generateFileResult("Brute Force Solution", bruteForceSolution);
			cout << "Time of Brute Force Solution with " << cities.size() << " vertices: " << bruteForceSolution.getTime() << endl;

			Solution brachAndBoundSolution = BranchAndBoundSolution().loadSolution(cities);
			Util().generateFileResult("Branch and Bound Solution", brachAndBoundSolution);
			cout << "Time of Branch and Bound Solution with " << cities.size() << " vertices: " << brachAndBoundSolution.getTime() << endl;

			Solution geneticSolution = GeneticSolution().loadSolution(cities);
			Util().generateFileResult("Genetic Solution", geneticSolution);
			cout << "Time of Genetic Solution with " << cities.size() << " vertices: " << geneticSolution.getTime() << endl;
			
			cout << endl;
		}
	}
	catch (runtime_error & e) {
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}