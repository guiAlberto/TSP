#pragma once

#include <sstream>
using namespace std;

class MutationException : public exception
{
public:
	MutationException();
	~MutationException();
};

