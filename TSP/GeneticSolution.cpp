#include "GeneticSolution.h"
#include "Util.h"
#include "ReproductionException.h"
#include "MutationException.h"

Chromosome GeneticSolution::mutate(Chromosome chromosome)
{
	vector<City> cities = chromosome.getCities();
	int firstIndex = Util().loadRandomNumber(0, cities.size() - 1);
	int secondIndex = Util().loadRandomNumber(0, cities.size() - 1);
	// defini��o hardcode que a chance de um cromossomo fazer muta��o � de 20%
	double chanceToMutate = 20;
	
	if (chromosome.isGoingToMutate(chanceToMutate)) {
		swap(cities[firstIndex], cities[secondIndex]);
	}
	
	// verifica se a muta��o gerada � inv�lida
	if (isInvalid(cities)) {
		throw MutationException();
	}
	return Chromosome(cities, Util().loadDistance(cities));
}

// tanto faz se os par�metros para corte e preced�ncia de gera��o do filho forem tomados do cromossomo macho ou f�mea
Chromosome GeneticSolution::reproduce(Chromosome male, Chromosome female)
{	
	// define uma posi��o aleat�ria de corte
	size_t cutPosition = Util().loadRandomNumber(0, male.getCities().size());
	vector<City> cities;
	for (size_t i = 0; i < male.getCities().size(); i++) {
		// o que estiver antes do corte vem do cromossomo macho
		if (i < cutPosition) {
			cities.push_back(male.getCities().at(i));
		}
		// o que estiver igual ou depois da posi��o de corte vem do cromossomo f�mea
		else {
			cities.push_back(female.getCities().at(i));
		}
	}

	// verifica se o filho gerado � inv�lida
	if (isInvalid(cities)) {
		throw ReproductionException();
	}

	return Chromosome(cities, Util().loadDistance(cities));
}

vector<Chromosome> GeneticSolution::loadFitstGeneration(vector<City> cities)
{
	vector<Chromosome> chromosomes;

	while (chromosomes.size() < cities.size()) {
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

vector<Chromosome> GeneticSolution::naturalSelection(vector<Chromosome> lastGeneration, int threshold)
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
	
	// defini��o hardcode no n�mero de gera��es, n�mero de muta��es e n�mero de reprodu��es
	size_t numberOfGenerations = 5;
	size_t numberOfMutations = actualGeneration.size() / 2;
	size_t numberOfReproductions = actualGeneration.size() / 2;
	
	// para cada gera��o...
	for (size_t i = 0; i < numberOfGenerations; i++) {
		
		// para cada muta��o
		for(size_t j = 0; j < numberOfMutations; j++){
			try {
				Chromosome chromossomeToMutate = actualGeneration.at(Util().loadRandomNumber(0, actualGeneration.size() - 1));
				Chromosome mutation = mutate(chromossomeToMutate);
				actualGeneration.push_back(mutation);
			}
			catch (MutationException) {
				//N�o faz nada, a muta��o � inv�lida
			}
		}

		// para cada reprodu��o
		for (size_t j = 0; j < numberOfReproductions; j++) {
			Chromosome male = actualGeneration.at(Util().loadRandomNumber(0, actualGeneration.size() - 1));
			Chromosome female = actualGeneration.at(Util().loadRandomNumber(0, actualGeneration.size() - 1));
			try {
				Chromosome child = reproduce(male, female);
				actualGeneration.push_back(child);
			}
			catch (ReproductionException) {
				//N�o fazer nada, o filho � inv�lido
			}
		}

		// sele��o natural filtra a gera��o com o limite do n�mero de v�rtices no grafo, essa regra pode ser alterada
		actualGeneration = naturalSelection(actualGeneration, cities.size());
	}
	Chromosome best = loadBestChromosome(actualGeneration);
	best.popCity();

	double endTime = Util().timer();
	double time = endTime - startTime;
	return Solution(best.getCities(), best.getCost(), time);
}
