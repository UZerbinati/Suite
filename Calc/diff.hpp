#ifndef DIFFHEADERDEF
#define DIFFHEADERDEF

#include <iostream>
#include <string>

using namespace std;

class Diff
{
	private:
		double (*f)(double x);
		double h;
		string type;
	public:
		Diff(double(*g)(double x));
		double call(double x);
};

#endif
