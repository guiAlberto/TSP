#include "BruteForceSolution.h"
#include "Util.h"

BruteForceSolution::BruteForceSolution()
{
}

BruteForceSolution::~BruteForceSolution()
{
}

vector<vector<City>> BruteForceSolution::loadCitiesPermutation(vector<City> cities, vector<vector<City>> permutation, int l, int r) {
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

vector<vector<City>> BruteForceSolution::loadCitiesPermutation(vector<City> cities) {
	// resolution found in https://goo.gl/AqHmnS
	vector<vector<City>> permutation;
	int n = cities.size() - 1;
	permutation = loadCitiesPermutation(cities, permutation, 0, n);
	return permutation;
}

Solution BruteForceSolution::loadSolution(vector<City> cities) {
	double startTime = Util().timer();
	
	// gera todas as permuta��es dado um conjunto de cidades
	vector<vector<City>> permutation = loadCitiesPermutation(cities);
	
	// a melhor solu��o inicial � a primeira
	Solution bestSolution;
	bestSolution.setDistance(0);
	bestSolution.setCities(permutation.at(0));

	for (size_t i = 1; i < permutation.size(); i++) {
		vector<City> citiesTemp = permutation.at(i);
		double distanceTemp = Util().loadDistance(citiesTemp);
		distanceTemp += Util().loadDistance(citiesTemp.front(), citiesTemp.back());
		
		// se a solu��o atual for melhor do que a bestSolution, essa atual � a melhor
		if (distanceTemp < bestSolution.getDistance()) {
			bestSolution.setDistance(distanceTemp);
			bestSolution.setCities(citiesTemp);
		}
	}

	double endTime = Util().timer();
	double time = endTime - startTime;
	bestSolution.setTime(time);
	
	return bestSolution;
}
