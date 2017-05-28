#pragma once

#include <sstream>
using namespace std;

class ReproductionException : public exception
{
public:
	ReproductionException();
	~ReproductionException();
};

