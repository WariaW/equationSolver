#pragma once
#include "EquationsSet.h"
#include <iostream>
using namespace std;

class SimultaneousEquationsSolver
{
	EquationsSet equations;
	double *solution;

public:

	SimultaneousEquationsSolver();
	SimultaneousEquationsSolver(const EquationsSet &equations);
	~SimultaneousEquationsSolver();

	void upperTriangularMatrix();
	void printMatrix(double **matrix);
	int numberOfSolutions(double **matrix);
	void oneSolution();
	void printSolution();

	EquationsSet getEquations()
	{
		return equations;
	}

	void setEquations(const EquationsSet &e)
	{
		equations = e;
	}

private:
	void swapRows(double **matrix, int r1, int r2);
};


