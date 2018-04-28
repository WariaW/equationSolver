#include "EquationsSet.h"
#include <string>

EquationsSet::EquationsSet()
{
	equationsAmount = 0;
	variablesAmount = 0;
	variablesNames = NULL;
	coefficients = NULL;
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
	delete
}
