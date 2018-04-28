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
	if (tempLines == NULL)
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

// WHOLE FUNCTION TO IMPLEMENT CORRECTLY !!!
EquationsSet FileDataOperations::extractEquations()
{
	string variables;
	// loop for each line
	for (int i = 0; i < readedLinesAmount; i++)
	{
		string temp = readedLines[i];
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
			if (temp[c] == '-')
			{
				coefficientNegative = true;
			}
			if (isdigit(temp[c]) || temp[c] == '.')
			{
				numberString += temp[c];
				if (!numberStarted)
				{
					numberStarted = true;
				}
			}
			else if (numberStarted)
			{
				
			}
			if ((temp[c] >= 65 && temp[c] <= 90) || (temp[c] >= 97 && temp[c] <= 122))
			{
				int varIndex = findIndexOfVariable(variables, temp[c]);
				if (varIndex == -1)
				{
					variables += temp[c];
					++varIndex;
				}
				if (numberStarted)
				{
					// printing
					if (coefficientNegative)
					{
						cout << (stod(numberString) * (-1)) << endl;
					}
					else
					{
						cout << numberString << endl;
					}
					numberStarted = false;
				}
				else
				{
					if (coefficientNegative)
					{
						cout << -1 << endl;
					}
					else
					{
						cout << 1 << endl;
					}
				}
				cout << temp[c] << " as var with index: " << varIndex << endl;
			}

		}
	}

	return EquationsSet();
}
