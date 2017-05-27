#include "BranchAndBoundSolution.h"

vector<City> allCities;

BranchAndBoundSolution::BranchAndBoundSolution()
{
}


BranchAndBoundSolution::~BranchAndBoundSolution()
{
}

Solution BranchAndBoundSolution::loadSolution(vector<City> cities)
{
	allCities = cities;

	vector<Path> paths;
	Path bestPath;
	vector<City> firstCity;
	firstCity.push_back(allCities.at(0));

	paths.push_back(Path(firstCity, 0));
	bestPath = loadBestPath(paths);

	// Avaliação do bestPath.size() com allCities.size() + 1 por causa da aresta que volta para o ponto inicial
	while (bestPath.size() < (allCities.size() + 1)) {
		vector<Path> children = expandChildren(bestPath);
		paths = addAll(paths, children);
		paths = removePath(paths, bestPath);
		bestPath = loadBestPath(paths);
	}
	// Remover ultimo elemento das cidades, que é igual ao primeiro
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
	else {
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
