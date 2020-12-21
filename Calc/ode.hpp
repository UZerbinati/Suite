#ifndef ODEHEADDEF
#define ODEHEADDEF

#include "../suite.hpp"
#include <iostream>
#include <functional>
#include <vector>

using namespace std;

class LinearODE
{
// K2(t) du/dt + K1(t) u + K0(t) = 0; 
	private:
		int order;
		std::function <double(double)> K[10];
		double a;
		double b;
		double I0;
		string form;
	public:
		LinearODE();
		LinearODE(int order);
		string toString();
		void setDomain(double a,double b);
		void setIC(double y0);
		void setCoefficient(int k,std::function<double(double)> f);
		std::tuple<std::vector<double>,std::vector<double>> ScalarEuler(double h);

};
#endif
