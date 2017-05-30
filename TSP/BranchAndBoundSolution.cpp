#include "BranchAndBoundSolution.h"
#include "Util.h"

vector<City> allCities;
double inf = std::numeric_limits<double>::infinity();


BranchAndBoundSolution::BranchAndBoundSolution()
{
}


BranchAndBoundSolution::~BranchAndBoundSolution()
{
}

Solution BranchAndBoundSolution::loadSolution(vector<City> cities)
{
	double startTime = Util().timer();
	allCities = cities;

	City firstCity = cities.front();
	vector<City> firstCityVector;
	firstCityVector.push_back(firstCity);
	double firstCost = 0;

	Branch firstBranch = Branch(firstCityVector, firstCost);
	vector<Branch> branches;
	branches.push_back(firstBranch);

	Branch bestBranch = Branch(vector<City>(), INFINITY);

	while (branches.size() > 0) {
		Branch actualBranch = branches.back();
		branches.pop_back();
		
		//bound
		if (actualBranch.getCost() > bestBranch.getCost()) {
			continue;
		}

		vector<Branch> children = expandChildren(actualBranch);
		for (size_t i = 0; i < children.size(); i++) {
			Branch child = children.at(i);
			branches.push_back(child);
		}
		if (branches.size() > 0) {
			actualBranch = branches.back();
		}
		if ((actualBranch.size() == (allCities.size() + 1)) && actualBranch.getCost() < bestBranch.getCost()) {
			bestBranch = actualBranch;
			branches.pop_back();
		}
	}
	bestBranch.popCity();

	double endTime = Util().timer();
	double time = endTime - startTime;
	return Solution(bestBranch.getCities(), bestBranch.getCost(), time);
}

vector<Branch> BranchAndBoundSolution::addAll(vector<Branch> branches, vector<Branch> children)
{
	for (size_t i = 0; i < children.size(); i++) {
		Branch child = children.at(i);
		branches.push_back(children.at(i));
	}
	return branches;
}


vector<Branch> BranchAndBoundSolution::expandChildren(Branch originalBranch)
{
	vector<City> children;
	for (size_t i = 0; i < allCities.size(); i++) {
		City city_i = allCities.at(i);
		bool contains = false;
		for (size_t j = 0; j < originalBranch.getCities().size(); j++) {
			City city_j = originalBranch.getCities().at(j);
			if (city_i.getId() == city_j.getId()) {
				contains = true;
				break;
			}
		}
		if (!contains) {
			children.push_back(city_i);
		}
	}

	vector<Branch> expandedBranches;
	if (children.size() > 0) {
		for (size_t i = 0; i < children.size(); i++) {
			City newCity = children.at(i);
			Branch newBranch = originalBranch;
			newBranch.putCity(newCity);
			expandedBranches.push_back(newBranch);
		}
	}
	//Volta do ultimo vertice para o inicial
	else if(originalBranch.size() == allCities.size()){
		City newCity = allCities.front();
		Branch newBranch = originalBranch;
		newBranch.putCity(newCity);
		expandedBranches.push_back(newBranch);
	}
	return expandedBranches;
}

vector<Branch> BranchAndBoundSolution::removeBranch(vector<Branch> originalBranch, Branch branchToRemove)
{
	vector<Branch> newBranch;

	for (size_t i = 0; i < originalBranch.size(); i++) {
		Branch branch = originalBranch.at(i);
		if (!branchToRemove.equals(branch)) {
			newBranch.push_back(branch);
		}
	}
	return newBranch;
}
