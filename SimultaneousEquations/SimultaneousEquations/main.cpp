#include <iostream>
#include "EquationsSet.h"
#include "FileDataOperations.h"
#include "SimultaneousEquationsSolver.h"
#define PATHS_AMOUNT 2

int main()
{
	cout << "hello world!" << endl;
	string paths[PATHS_AMOUNT];
	for (int p = 0; p < PATHS_AMOUNT; p++)
	{
		paths[p] = "equations" + to_string(p) + ".txt";
		FileDataOperations Fdo(paths[p]);
		Fdo.readLines();
		EquationsSet es = Fdo.extractEquations();
		es.printCoefficients();
		SimultaneousEquationsSolver ses(es);
		ses.upperTriangularMatrix();
		ses.printMatrix(ses.equations.getCoefficients());
		cout<<"Number of solutios = "<<ses.numberOfSolutions(ses.equations.getCoefficients())<<endl;
	}
	
	getchar();
	return 0;
}

