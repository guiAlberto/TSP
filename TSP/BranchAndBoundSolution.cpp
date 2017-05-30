#include "BranchAndBoundSolution.h"

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
	allCities = cities;


	City firstCity = cities.front();
	vector<City> firstCityVector;
	firstCityVector.push_back(firstCity);
	double firstCost = 0;

	Path firstPath = Path(firstCityVector, firstCost);
	vector<Path> paths;
	paths.push_back(firstPath);

	Path bestPath = Path(vector<City>(), INFINITY);

	while (paths.size() > 0) {
		Path actualPath = paths.back();
		paths.pop_back();
		
		//bound
		if (actualPath.getCost() > bestPath.getCost()) {
			continue;
		}

		vector<Path> children = expandChildren(actualPath);
		for (size_t i = 0; i < children.size(); i++) {
			Path child = children.at(i);
			paths.push_back(child);
		}
		if (paths.size() > 0) {
			actualPath = paths.back();
		}
		if ((actualPath.size() == (allCities.size() + 1)) && actualPath.getCost() < bestPath.getCost()) {
			bestPath = actualPath;
			paths.pop_back();
		}
	}
	bestPath.popCity();
	return Solution(bestPath.getCities(), bestPath.getCost());
}

Path BranchAndBoundSolution::loadBestPath(vector<Path> paths)
{
	Path bestPath;
	for (size_t i = 0; i < paths.size(); i++) {
		Path path = paths.at(i);
		if (i == 0) {
			bestPath = path;
		}
		else {
			if (path.getCost() < bestPath.getCost()) {
				bestPath = path;
			}
		}
	}
	return bestPath;

}

vector<Path> BranchAndBoundSolution::addAll(vector<Path> paths, vector<Path> children)
{
	for (size_t i = 0; i < children.size(); i++) {
		Path child = children.at(i);
		paths.push_back(children.at(i));
	}
	return paths;
}


vector<Path> BranchAndBoundSolution::expandChildren(Path originalPath)
{
	vector<City> children;
	for (size_t i = 0; i < allCities.size(); i++) {
		City city_i = allCities.at(i);
		bool contains = false;
		for (size_t j = 0; j < originalPath.getCities().size(); j++) {
			City city_j = originalPath.getCities().at(j);
			if (city_i.getId() == city_j.getId()) {
				contains = true;
				break;
			}
		}
		if (!contains) {
			children.push_back(city_i);
		}
	}

	vector<Path> expandedPaths;
	if (children.size() > 0) {
		for (size_t i = 0; i < children.size(); i++) {
			City newCity = children.at(i);
			Path newPath = originalPath;
			newPath.putCity(newCity);
			expandedPaths.push_back(newPath);
		}
	}
	//Volta do ultimo vertice para o inicial
	else if(originalPath.size() == allCities.size()){
		City newCity = allCities.front();
		Path newPath = originalPath;
		newPath.putCity(newCity);
		expandedPaths.push_back(newPath);
	}
	return expandedPaths;
}

vector<Path> BranchAndBoundSolution::removePath(vector<Path> originalPaths, Path pathToRemove)
{
	vector<Path> newPath;

	for (size_t i = 0; i < originalPaths.size(); i++) {
		Path path = originalPaths.at(i);
		if (!pathToRemove.equals(path)) {
			newPath.push_back(path);
		}
	}
	return newPath;
}
