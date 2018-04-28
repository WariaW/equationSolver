#include "EquationsSet.h"


EquationsSet::EquationsSet()
{
	equationsAmount = 0;
	variablesAmount = 0;
	variablesNames = NULL;
	coefficients = NULL;
}

EquationsSet::EquationsSet(const EquationsSet & item)
{
	this->equationsAmount = item.equationsAmount;
	this->variablesAmount = item.variablesAmount;
	this->variablesNames = new string[variablesAmount];
	if (this->variablesNames == nullptr)
	{
		cout << "Cannot allocate memory while copying object." << endl;
	}
	for (int i = 0; i < item.variablesAmount; i++)
	{
		this->variablesNames[i] = item.variablesNames[i];
	}
	// copying coefficients matrix
	this->coefficients = new (nothrow) double*[item.equationsAmount];
	if (this->coefficients == nullptr)
	{
		cout << "Cannot allocate memory while copying object." << endl;
	}
	for (int i = 0; i < item.variablesAmount; i++)
	{
		this->coefficients[i] = new double[variablesAmount];
		if (this->coefficients[i] == nullptr)
		{
			cout << "Cannot allocate memory while copying object." << endl;
		}
	}
	for (int x = 0; x < equationsAmount; x++)
	{
		for (int y = 0; y < variablesAmount; y++)
		{
			this->coefficients[x][y] = item.coefficients[x][y];
		}
	}
}


EquationsSet::~EquationsSet()
{
	if (equationsAmount > 0)
	{
		for (int i = 0; i < equationsAmount; i++)
		{
			delete[] coefficients[i];
		}
	}
	delete[] coefficients;
	delete[] variablesNames;
}
