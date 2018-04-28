#pragma once


#include "EquationsSet.h"
using namespace std;
class SimultaneousEquationsSolver
{
	//EquationsSet equations;
public:
	//SimultaneousEquationsSolver(EquationsSet equations);
	~SimultaneousEquationsSolver();

	template <size_t rows, size_t cols>
	void upperTriangularMatrix(int(&matrix)[rows][cols]);

	template <size_t rows, size_t cols>
	void swapRows(int(&matrix)[rows][cols], int r1, int r2);

};


