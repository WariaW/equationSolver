#pragma once
#include <iostream>
#include <new>
#include <string>

using namespace std;

class EquationsSet
{
private:
	int equationsAmount;
	int variablesAmount;
	string variablesNames;
	double **coefficients;

public:
	EquationsSet();
	EquationsSet(const EquationsSet & item);
	~EquationsSet();

	void setCoefficients(double **tempCoefficients, size_t eqs, size_t cols);
	double **getCoefficients();
	void setVariablesNames(string varsNames) { variablesNames = varsNames; }
	string getVariablesNames() { return variablesNames; }
	int getEquationsAmount() { return equationsAmount; }
	int getVariablesAmount() { return variablesAmount; }

	void printCoefficients();
	// operators overloading
	EquationsSet& operator=(const EquationsSet& rightSide);
};

