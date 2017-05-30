#include "GeneticSolution.h"
#include "Util.h"
#include "ReproductionException.h"
#include "MutationException.h"

size_t threshold;
double chanceToMutate = 20;

Chromosome GeneticSolution::mutate(Chromosome chromosome)
{
	vector<City> cities = chromosome.getCities();
	int firstIndex = Util().loadRandomNumber(0, cities.size() - 1);
	int secondIndex = Util().loadRandomNumber(0, cities.size() - 1);
	if (chromosome.isGoingToMutate(chanceToMutate)) {
		swap(cities[firstIndex], cities[secondIndex]);
	}
	if (isInvalid(cities)) {
		throw MutationException();
	}
	return Chromosome(cities, Util().loadDistance(cities));
}

Chromosome GeneticSolution::reproduce(Chromosome c1, Chromosome c2)
{
	size_t cutPosition = Util().loadRandomNumber(0, c1.getCities().size());
	vector<City> cities;
	for (size_t i = 0; i < c1.getCities().size(); i++) {
		if (i < cutPosition) {
			cities.push_back(c1.getCities().at(i));
		}
		else {
			cities.push_back(c2.getCities().at(i));
		}
	}
	if (isInvalid(cities)) {
		throw ReproductionException();
	}

	return Chromosome(cities, Util().loadDistance(cities));
}

vector<Chromosome> GeneticSolution::loadFitstGeneration(vector<City> cities)
{
	vector<Chromosome> chromosomes;
	threshold = cities.size();

	while (chromosomes.size() < threshold) {
		vector<City> citiesCopy = cities;
		vector<City> newCities;
		while (citiesCopy.size() > 0) {
			int randomNumber = Util().loadRandomNumber(0, citiesCopy.size() - 1);
			City newCity = citiesCopy.at(randomNumber);
			newCities.push_back(newCity);
			citiesCopy = removeCity(citiesCopy, newCity);
		}
		newCities.push_back(newCities.front());
		chromosomes.push_back(Chromosome(newCities, Util().loadDistance(newCities)));
	}

	return chromosomes;
}

vector<Chromosome> GeneticSolution::naturalSelection(vector<Chromosome> lastGeneration)
{
	vector<Chromosome> newGeneration;

	for (size_t i = 0; i < threshold; i++) {
		newGeneration.push_back(lastGeneration.at(i));
	}

	Chromosome worst = loadWorstChromosome(newGeneration);

	for (size_t i = threshold; i < lastGeneration.size(); i++) {
		if (lastGeneration.at(i).getCost() < worst.getCost()) {
			newGeneration.push_back(lastGeneration.at(i));
			newGeneration = removeChromossome(newGeneration, worst);
			worst = loadWorstChromosome(newGeneration);
		}
	}

	return newGeneration;
}

bool GeneticSolution::isInvalid(vector<City> cities)
{
	for(size_t i = 0; i < cities.size() - 1; i++){
		for (size_t j = i + 1; j < cities.size(); j++) {
			if(cities.at(i).getId() == cities.at(j).getId()){
				return true;
			}
		}
	}

	if (!cities.front().equals(cities.back())) {
		return true;
	}

	return false;
}

vector<City> GeneticSolution::removeCity(vector<City> originalCities, City cityToRemove)
{
	vector<City> newCities;

	for (size_t i = 0; i < originalCities.size(); i++) {
		City city = originalCities.at(i);
		if (!cityToRemove.equals(city)) {
			newCities.push_back(city);
		}
	}
	return newCities;
}

vector<Chromosome> GeneticSolution::removeChromossome(vector<Chromosome> originalChromosomes, Chromosome chromosomeToRemove)
{
	vector<Chromosome> newChromosomes;

	for (size_t i = 0; i < originalChromosomes.size(); i++) {
		Chromosome chromosome = originalChromosomes.at(i);
		if (!chromosomeToRemove.equals(chromosome)) {
			newChromosomes.push_back(chromosome);
		}
	}
	return newChromosomes;
}

Chromosome GeneticSolution::loadWorstChromosome(vector<Chromosome> chromosomes)
{
	Chromosome worst = chromosomes.at(0);
	for (size_t i = 1; i < chromosomes.size(); i++) {
		Chromosome chromosome = chromosomes.at(i);
		if (chromosome.getCost() > worst.getCost()) {
			worst = chromosome;
		}
	}
	return worst;
}

Chromosome GeneticSolution::loadBestChromosome(vector<Chromosome> chromosomes)
{
	Chromosome best = chromosomes.at(0);
	for (size_t i = 1; i < chromosomes.size(); i++) {
		Chromosome chromosome = chromosomes.at(i);
		if (chromosome.getCost() < best.getCost()) {
			best = chromosome;
		}
	}
	return best;
}

GeneticSolution::GeneticSolution()
{
}


GeneticSolution::~GeneticSolution()
{
}

Solution GeneticSolution::loadSolution(vector<City> cities)
{
	double startTime = Util().timer();

	vector<Chromosome> actualGeneration = loadFitstGeneration(cities);
	size_t numberOfGenerations = 5;
	size_t numberOfMutations = actualGeneration.size() / 2;
	size_t numberOfReproductions = actualGeneration.size() / 2;
	for (size_t i = 0; i < numberOfGenerations; i++) {
		for(size_t j = 0; j < numberOfMutations; j++){
			try {
				Chromosome chromossomeToMutate = actualGeneration.at(Util().loadRandomNumber(0, actualGeneration.size() - 1));
				Chromosome mutation = mutate(chromossomeToMutate);
				actualGeneration.push_back(mutation);
			}
			catch (MutationException) {
				//Não faz nada, a mutação é inválida
			}
		}

		for (size_t j = 0; j < numberOfReproductions; j++) {
			Chromosome male = actualGeneration.at(Util().loadRandomNumber(0, actualGeneration.size() - 1));
			Chromosome female = actualGeneration.at(Util().loadRandomNumber(0, actualGeneration.size() - 1));
			try {
				Chromosome child = reproduce(male, female);
				actualGeneration.push_back(child);
			}
			catch (ReproductionException) {
				//Não fazer nada, o filho é inválido
			}
		}

		actualGeneration = naturalSelection(actualGeneration);
	}
	Chromosome best = loadBestChromosome(actualGeneration);
	best.popCity();

	double endTime = Util().timer();
	double time = endTime - startTime;
	return Solution(best.getCities(), best.getCost(), time);
}
