#include "SimultaneousEquationsSolver.h"



SimultaneousEquationsSolver::SimultaneousEquationsSolver() : equations()
{
}

SimultaneousEquationsSolver::SimultaneousEquationsSolver(const EquationsSet &input_equations) : equations(input_equations)
{
	solution = new double[equations.getVariablesAmount()];
}

SimultaneousEquationsSolver::~SimultaneousEquationsSolver()
{
	delete[] solution;
}

void SimultaneousEquationsSolver::upperTriangularMatrix()
{
	double **matrix = equations.getCoefficients();
	double coefficient = 0;
	int swap = -1;
	for (int i = 0; i < equations.getEquationsAmount(); i++) //przejœcie po wierszach
	{
		for (int j = i + 1; j < equations.getEquationsAmount(); j++) //wiersz od którego siê odejmuje wiersz wy¿ej
		{
			while (matrix[i][i] == 0)
			{
				swap = i;
				while (matrix[swap][i] == 0)
				{
					swap++;
					if (swap == equations.getEquationsAmount())
					{
						i++;
						j++;
						swap = i;
						if (i > equations.getEquationsAmount())
						{
							break;
						}
					}
				}
				if (swap > i)
				{
					swapRows(matrix, i, swap);
				}
			}
			coefficient = matrix[j][i] / matrix[i][i];
			for (int k = i; k < equations.getVariablesAmount() + 1; k++)	//kolejne elementy wiersza do odejmowania
			{
				matrix[j][k] = matrix[j][k] - matrix[i][k] * coefficient;
			}
		}
	}
}


void SimultaneousEquationsSolver::swapRows(double **matrix, int r1, int r2)
{
	double *tempRow = new double[equations.getVariablesAmount() + 1];
	for (int i = 0; i < equations.getEquationsAmount(); i++)
	{
		tempRow[i] = matrix[r1][i];
		matrix[r1][i] = matrix[r2][i];
		matrix[r2][i] = tempRow[i];
	}
	delete [] tempRow;
}

void SimultaneousEquationsSolver::printMatrix(double **matrix)
{
	for (size_t r = 0; r < equations.getEquationsAmount(); r++)
	{
		for (size_t c = 0; c < equations.getVariablesAmount() + 1; c++)
		{
			cout << matrix[r][c] << "	";
		}
		cout << endl;
	}
	cout << endl;
}

int SimultaneousEquationsSolver::numberOfSolutions(double **matrix)
{
	int zeroRowsACounter = 0;
	int zeroRowsUCounter = 0;
	int numberOfS = 0;
	size_t c = 0;
	for (size_t r = 0; r < equations.getEquationsAmount(); r++)
	{
		while (matrix[r][c] == 0)
		{
			if (c == equations.getVariablesAmount() + 1 - 2)
			{
				zeroRowsACounter++;
			}
			if (c == equations.getVariablesAmount() + 1 - 1)
			{
				zeroRowsUCounter++;
				break;
			}
			c++;
		}
		c = 0;
	}
	if (equations.getVariablesAmount() > equations.getEquationsAmount())
	{
		zeroRowsACounter += (equations.getVariablesAmount() - equations.getEquationsAmount());
		zeroRowsUCounter += (equations.getVariablesAmount() - equations.getEquationsAmount());
	}
	if (zeroRowsACounter == 0 && zeroRowsUCounter == 0)
	{
		numberOfS = 0; //<- Equations have only one solution
	}
	else if (zeroRowsACounter == zeroRowsUCounter && zeroRowsACounter > 0)
	{
		numberOfS = zeroRowsACounter;	//<- Equations have infinite number of solutions dependent on numbersOfS parameters
	}
	else if (zeroRowsACounter > zeroRowsUCounter)
	{
		numberOfS = -1;	//<- Equations are contradictory
	}
	return numberOfS;
}

void SimultaneousEquationsSolver::oneSolution()
{
	for (int i = equations.getVariablesAmount(); i > 0; i--)
	{
		solution[i - 1] = equations.getCoefficients()[i - 1][equations.getVariablesAmount()];
		for (int j = i; j < equations.getVariablesAmount(); j++)
		{
			solution[i - 1] -= (equations.getCoefficients()[i - 1][j] * solution[j]);
		}
		solution[i - 1] /= equations.getCoefficients()[i - 1][i - 1];
	}
}

void SimultaneousEquationsSolver::printSolution()
{
	for (int i = 0; i < equations.getVariablesAmount(); i++)
	{
		cout << equations.getVariablesNames()[i] << " = " << solution[i] << endl;
	}
}
