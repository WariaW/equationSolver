#pragma once
#ifndef EQUATIONSSET_H
#define EQUATIONSSET_H

#include <iostream>
#include <new>
#include <string>

using namespace std;

class EquationsSet
{
private:
	int equationsAmount;
	int variablesAmount;
	string *variablesNames;
	double **coefficients;

public:
	EquationsSet();
	EquationsSet(const EquationsSet & item);
	~EquationsSet();
};

#endif // !EQUATIONSSET_H



