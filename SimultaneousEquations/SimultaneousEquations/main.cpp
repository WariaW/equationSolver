#include <iostream>
#include <string>
#include "EquationsSet.h"
#include "FileDataOperations.h"


int main()
{
	cout << "hello world!" << endl;
	string path = "C:\\Users\\Micha�\\Desktop\\equations.txt";
	FileDataOperations Fdo(path);
	Fdo.readLines();
	EquationsSet ES = Fdo.extractEquations();
	getchar();
}