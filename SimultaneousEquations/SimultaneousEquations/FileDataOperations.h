#pragma once
#ifndef FILEDATAOPERATIONS_H
#define FILEDATAOPERATIONS_H

#include <fstream>
#include <string>
#include <istream>
#include <iostream>
#include <cctype>
#include "EquationsSet.h"

using namespace std;

class FileDataOperations
{
private:
	string inputFilePath;
	string outputFilePath;
	ifstream infile;
	ofstream outfile;
	int readedLinesAmount;
	string *readedLines;
	int findIndexOfVariable(string variables, char variable);

public:
	FileDataOperations();
	FileDataOperations(string inputPath);
	FileDataOperations(string inputPath, string outputPath);
	~FileDataOperations();

	inline int getLinesAmount() { return readedLinesAmount; }
	void readLines();
	EquationsSet extractEquations();

};

#endif // !FILEDATAOPERATIONS_H



