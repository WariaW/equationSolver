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
	~EquationsSet();
};

