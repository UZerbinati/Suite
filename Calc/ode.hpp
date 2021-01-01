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
		std::function <T(double)> K[10];
		double a;
		double b;
		T I0;
		string form;
		string solver;
		int solverIT;
	public:
		LinearODE();
		LinearODE(int order);
		string toString();
		void setDomain(double a,double b);
		void setIC(T y0);
		void setSolver(string stype, int sIT);
		void setCoefficient(int k,std::function<T(double)> f);
		std::tuple<std::vector<double>,std::vector<T>> ScalarEuler(double h);

};

template <> class LinearODE<vec>
{
// K2(t) du/dt + K1(t) u + K0(t) = 0; 
	private:
		int order;
		std::function <spmat (double)> K[10];
		double a;
		double b;
		vec* I0;
		string form;
		string solver;
		int solverIT;
	public:
		LinearODE();
		LinearODE(int order);
		string toString();
		void setDomain(double a,double b);
		void setIC(vec y0);
		void setSolver(string stype, int sIT);
		void setCoefficient(int k,std::function<spmat(double)> f);
		std::tuple<std::vector<double>,std::vector<vec>> ScalarEuler(double h);

};

template <class T> class NonLinearODE
{
/* Our aim is to solve ODE of the form,
 * 	f: T x T x ... x T x R -> T
 * 
*/ 
	private:
		int order;
		std::function <T(std::vector<T>,double)> K;
		std::function <T(double)> M; 
		double a;
		double b;
		T I0;
		string form;
		string solver;
		int solverIT;
	public:
		NonLinearODE();
		NonLinearODE(int order);
		string toString();
		void setDomain(double a,double b);
		void setIC(T y0);
		void setSolver(string stype, int sIT);
		void setCoefficients(std::function<T(double)> m,std::function<T(std::vector<T>,double)> k);
		std::tuple<std::vector<double>,std::vector<T>> Euler(double h);

};
#endif
