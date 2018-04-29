#include "EquationsSet.h"


EquationsSet::EquationsSet()
{
	equationsAmount = 0;
	variablesAmount = 0;
	variablesNames = "";
	coefficients = nullptr;
	cout << "EquationsSet constructor called!" << endl;
}

EquationsSet::EquationsSet(const EquationsSet & item)
{
	this->equationsAmount = item.equationsAmount;
	this->variablesAmount = item.variablesAmount;
	this->variablesNames = item.variablesNames;
	// copying coefficients matrix
	this->coefficients = new (nothrow) double*[item.equationsAmount];
	if (this->coefficients == nullptr)
	{
		cout << "Cannot allocate memory while copying object." << endl;
	}
	for (int i = 0; i < item.equationsAmount; i++)
	{
		this->coefficients[i] = new double[variablesAmount + 1];
		if (this->coefficients[i] == nullptr)
		{
			cout << "Cannot allocate memory while copying object." << endl;
		}
	}
	for (int y = 0; y < equationsAmount; y++)
	{
		for (int x = 0; x < variablesAmount + 1; x++)
		{
			this->coefficients[y][x] = item.coefficients[y][x];
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
	cout << "EquationsSet destructor called!" << endl;
}

double ** EquationsSet::getCoefficients()
{
	if (coefficients != nullptr)
	{
		return coefficients;
	}
	else
	{
		cerr << "coefficients pointer is nullptr" << endl;
		return nullptr;
	}
}

void EquationsSet::printCoefficients()
{
	for (int y = 0; y < equationsAmount; y++)
	{
		for (int x = 0; x < variablesAmount + 1; x++)
		{
			cout << coefficients[y][x] << "  ";
		}
		cout << endl;
	}
}

EquationsSet & EquationsSet::operator=(const EquationsSet & rightSide)
{
	EquationsSet temp = EquationsSet(rightSide);
	return temp;
}


void EquationsSet::setCoefficients(double **tempCoefficients, size_t eqs, size_t cols)
{
	try
	{
		coefficients = new (nothrow) double*[eqs];
		if (coefficients == nullptr)
		{
			throw bad_alloc();
		}
		for (int i = 0; i < eqs; i++)
		{
			coefficients[i] = new (nothrow) double[cols];
			if (coefficients[i] == nullptr)
			{
				throw bad_alloc();
			}
		}
		// fill coefficients matrix
		for (int y = 0; y < eqs; y++)
		{
			for (int x = 0; x < cols; x++)
			{
				coefficients[y][x] = tempCoefficients[y][x];
			}
		}
		// set other dependant parameters
		equationsAmount = eqs;
		variablesAmount = cols - 1;
	}
	catch (const bad_alloc & e)
	{
		cerr << "Cannot allocate memory for coefficients matrix" << endl;
		return;
	}
}

