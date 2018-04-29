#include "FileDataOperations.h"


FileDataOperations::FileDataOperations()
{
	inputFilePath = "";
	outputFilePath = "";
	readedLinesAmount = 0;
}

FileDataOperations::FileDataOperations(string inputPath) : inputFilePath(inputPath), infile(inputPath), readedLinesAmount(0)
{
}

FileDataOperations::FileDataOperations(string inputPath, string outputPath) : inputFilePath(inputPath), outputFilePath(outputPath), infile(inputPath), outfile(outputPath), readedLinesAmount(0)
{
}

FileDataOperations::~FileDataOperations()
{
	delete[] readedLines;
}

int FileDataOperations::findIndexOfVariable(string variables, char variable)
{
	for (int i = 0; i < variables.size(); i++)
	{
		if (variables[i] == variable)
		{
			return i;
		}
	}
	return -1;
}

void FileDataOperations::readLines()
{
	string s;
	int linesAmount = 0;
	while (getline(this->infile, s))
	{
		++linesAmount;
	}
	readedLinesAmount = linesAmount;
	// back to begin of file
	infile.clear();
	infile.seekg(0, ios::beg);
	// array of lines from file
	string *tempLines = new string[linesAmount];
	if (tempLines == nullptr)
	{
		cout << "bad allocation!" << endl;
	}
	int stringCounter = 0;
	string tempLine;
	cout << "raw line: " << tempLine << endl;
	while (getline(infile, tempLine))
	{
		cout << "current line: " << tempLine << endl;
		cout << "cnt: " << stringCounter << endl;
		tempLines[stringCounter] = tempLine;
		++stringCounter;
	}
	/*for (int cnt = 0; cnt < linesAmount; cnt++)
	{
		cout << tempLines[cnt] << endl;
	}*/
	readedLines = tempLines;
}


EquationsSet FileDataOperations::extractEquations()
{
	try
	{
		// search for all variables
		string variables = "";
		for (int i = 0; i < readedLinesAmount; i++)
		{
			string temp = readedLines[i];
			for (int c = 0; c < temp.size(); c++)
			{
				if ((temp[c] >= 65 && temp[c] <= 90) || (temp[c] >= 97 && temp[c] <= 122))
				{
					int varIndex = findIndexOfVariable(variables, temp[c]);
					if (varIndex == -1)
					{
						variables += temp[c];
						//++varIndex;
					}
				}
			}
		}
		// temporary coefficients matrix allocation
		double **tempCoefficients = new (nothrow) double*[readedLinesAmount];
		if (tempCoefficients == nullptr)
		{
			throw bad_alloc();
		}
		for (int y = 0; y < readedLinesAmount; y++)
		{
			tempCoefficients[y] = new (nothrow) double[variables.size() + 1];
			if (tempCoefficients[y] == nullptr)
			{
				throw bad_alloc();
			}
			// fill matrix with zeros
			for (int x = 0; x < variables.size() + 1; x++)
			{
				tempCoefficients[y][x] = 0.0;
			}
		}
		// loop for each line
		for (int i = 0; i < readedLinesAmount; i++)
		{
			string temp = readedLines[i];
			bool rightSide = false;
			bool numberStarted = false;
			bool coefficientNegative = false;
			string numberString = "";
			// loop for every character in line
			for (int c = 0; c < temp.size(); c++)
			{
				if (temp[c] == ' ')
				{
					continue;
				}
				if (temp[c] == '=')
				{
					if (numberStarted)
					{
						cerr << "Unknown behavior - number without variable name just before \"=\" sign" << endl;
					}
					rightSide = true;
					continue;
				}
				if (temp[c] == '-')
				{
					coefficientNegative = true;
					continue;
				}
				if (isdigit(temp[c]) || temp[c] == '.')
				{
					numberString += temp[c];
					numberStarted = numberStarted ? numberStarted : true;
				}
				// check if end of line and get value of the right side of equation
				if (c == (temp.size() - 1) && rightSide)
				{
					if (numberStarted)
					{
						tempCoefficients[i][variables.size()] = coefficientNegative ? (-1.0) * stod(numberString) : stod(numberString);
						coefficientNegative = false;
					}
					else
					{
						cerr << "No number on the right side of " << i << " equation" << endl;
					}
				}
				// if variable symbol appears eg. 'x' or 'y'
				if ((temp[c] >= 65 && temp[c] <= 90) || (temp[c] >= 97 && temp[c] <= 122))
				{
					int varIndex = findIndexOfVariable(variables, temp[c]);
					if (varIndex == -1)
					{
						throw exception("Cannot find specific variable name");
					}
					if (numberStarted)
					{
						tempCoefficients[i][varIndex] = coefficientNegative ? (-1.0) * stod(numberString) : stod(numberString);
						coefficientNegative = false;
						cout << tempCoefficients[i][varIndex] << endl;
						numberString = "";
						numberStarted = false;
					}
					else
					{
						tempCoefficients[i][varIndex] = coefficientNegative ? -1.0 : 1.0;
						coefficientNegative = false;
						cout << tempCoefficients[i][varIndex] << endl;
					}
					cout << temp[c] << " as var with index: " << varIndex << endl;
				}
			}
		}
		// printing tempCoefficients matrix
		for (int y = 0; y < readedLinesAmount; y++)
		{
			for (int x = 0; x < variables.size() + 1; x++)
			{
				cout << tempCoefficients[y][x] << "  ";
			}
			cout << endl;
		}
		// printing variables
		cout << "Variables in equations: " << variables << endl;
		// creating object to return
		EquationsSet es;
		es.setCoefficients(tempCoefficients, readedLinesAmount, variables.size() + 1);
		es.setVariablesNames(variables);
		// freeing memory 
		for (int y = 0; y < readedLinesAmount; y++)
		{
			delete[] tempCoefficients[y];
		}
		delete[] tempCoefficients;

		return es;
	}
	catch (const bad_alloc& e)
	{
		cerr << "Bad allocation" << endl;
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
	}
}
