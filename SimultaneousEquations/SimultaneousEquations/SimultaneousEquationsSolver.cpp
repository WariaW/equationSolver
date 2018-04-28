#include "SimultaneousEquationsSolver.h"



//SimultaneousEquationsSolver::SimultaneousEquationsSolver(EquationsSet equations)
//{
//	this->equations = equations;
//}

SimultaneousEquationsSolver::~SimultaneousEquationsSolver()
{
}

template <size_t rows, size_t cols>
void SimultaneousEquationsSolver::upperTriangularMatrix(int(&matrix)[rows][cols])
{
	int coefficient = 0;
	int swap = -1;
	for (int i = 0; i < /*equations.getEquationsAmount()*/ rows; i++) //przejœcie po wierszach
	{
		for (int j = i + 1; j < /*equations.getEquationsAmount()*/ rows; j++) //wiersz od którego siê odejmuje wiersz wy¿ej
		{
			while (matrix[i][i] == 0)
			{
				swap = i;
				while (matrix[swap][i] == 0)
				{
					swap++;
					if (swap == rows)
					{
						i++;
						j++;
						swap = i;
					}
				}
			}
			if (swap > i)
			{
				swapRows<rows, cols>(matrix, i, swap);
			}
			coefficient = matrix[j][i] / matrix[i][i];
			for (int k = i; k < /*equations.getVariablesAmount()*/cols; k++)	//kolejne elementy wiersza do odejmowania
			{
				matrix[j][k] = matrix[j][k] - matrix[i][k] * coefficient;
			}
		}
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << matrix[i][j] << "	";
		}
		cout << endl;
	}
}

template <size_t rows, size_t cols>
void SimultaneousEquationsSolver::swapRows(int(&matrix)[rows][cols], int r1, int r2)
{
	int tempRow[cols];
	for (int i = 0; i < cols; i++)
	{
		tempRow[i] = matrix[r1][i];
		matrix[r1][i] = matrix[r2][i];
		matrix[r2][i] = tempRow[i];
	}

}

