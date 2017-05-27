#pragma once

#include "Solution.h"
#include "Path.h"

using namespace std;

class BranchAndBoundSolution
{
private:
	vector<Path>expandChildren(Path);
	vector<Path> removePath(vector<Path>, Path);
public:
	BranchAndBoundSolution();
	~BranchAndBoundSolution();
	Solution loadSolution(vector<City>);
	Path loadBestPath(vector<Path>);
	vector<Path> addAll(vector<Path>, vector<Path>);
};

