#pragma once

#include "Solution.h"
#include "Chromosome.h"

class GeneticSolution
{
private:
	Chromosome mutate(Chromosome);
	Chromosome reproduce(Chromosome, Chromosome);
	vector<Chromosome> loadFitstGeneration(vector<City>);
	vector<Chromosome> naturalSelection(vector<Chromosome>, int);
	bool isInvalid(vector<City>);
	vector<City> removeCity(vector<City>, City);
	vector<Chromosome> removeChromossome(vector<Chromosome>, Chromosome);
	Chromosome loadWorstChromosome(vector<Chromosome>);
	Chromosome loadBestChromosome(vector<Chromosome>);
public:
	GeneticSolution();
	~GeneticSolution();
	Solution loadSolution(vector<City>);
};

