#pragma once
#include "EquationsSet.h"
#include <iostream>
using namespace std;

class SimultaneousEquationsSolver
{

public:
	EquationsSet equations;

	SimultaneousEquationsSolver();
	SimultaneousEquationsSolver(const EquationsSet &equations);
	~SimultaneousEquationsSolver();

	void upperTriangularMatrix();
	void printMatrix(double **matrix);
	int numberOfSolutions(double **matrix);

private:
	void swapRows(double **matrix, int r1, int r2);
};


