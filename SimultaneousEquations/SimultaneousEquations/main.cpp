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
		ses.printMatrix(ses.getEquations().getCoefficients());
		switch (ses.numberOfSolutions(ses.getEquations().getCoefficients()))
		{
		case -1:
			cout << "Equations are contradictory" << endl;
			break;
		case 0:
			cout << "Equations have one solution" << endl;
			ses.oneSolution();
			ses.printSolution();
			break;
		default:
			cout << "Equations have infinite number of solutions dependent on " << ses.numberOfSolutions(ses.getEquations().getCoefficients()) << " parameters" << endl;
			break;
		}

	}
	
	getchar();
	return 0;
}

