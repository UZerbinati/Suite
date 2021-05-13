#ifndef DIFFHEADERDEF
#define DIFFHEADERDEF

#include <iostream>
#include <string>
#include <functional>

using namespace std;

class Diff
{
	private:
		double h;
		string type;
		std::function <double(double)> f;
	public:

		Diff();
		double call(double x);
		void push(std::function <double(double)> g);
		void set_h(double step);
		void set_type(string fd);
};

#endif
