#include <iostream>
#include "EquationsSet.h"
#include "FileDataOperations.h"
#include "SimultaneousEquationsSolver.h"


int main()
{
	cout << "hello world!" << endl;
	string path = "C:\\Users\\Micha³\\Desktop\\equations.txt";
	FileDataOperations Fdo(path);
	Fdo.readLines();
	EquationsSet es = Fdo.extractEquations();
	es.printCoefficients();
	getchar();
	return 0;
}

