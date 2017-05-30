#pragma once

#include "Solution.h"
#include "Branch.h"

using namespace std;

class BranchAndBoundSolution
{
private:
	vector<Branch>expandChildren(Branch);
public:
	BranchAndBoundSolution();
	~BranchAndBoundSolution();
	Solution loadSolution(vector<City>);
	vector<Branch> addAll(vector<Branch>, vector<Branch>);
};

