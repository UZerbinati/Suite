#ifndef ODEHEADDEF
#define ODEHEADDEF

#include "../suite.hpp"
#include <iostream>
#include <functional>
#include <vector>

using namespace std;

template <class T> class LinearODE
{
// K2(t) du/dt + K1(t) u + K0(t) = 0; 
	private:
		int order;
		std::function <T(T)> K[10];
		double a;
		double b;
		T I0;
		string form;
	public:
		LinearODE();
		LinearODE(int order);
		string toString();
		void setDomain(double a,double b);
		void setIC(T y0);
		void setCoefficient(int k,std::function<T(T)> f);
		std::tuple<std::vector<T>,std::vector<T>> ScalarEuler(T h);

};
#endif
