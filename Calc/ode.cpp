#include "../suite.hpp"
#include "ode.hpp"
#include <functional>
#include <vector>

using namespace std;

//Due to the way we initzialize the array of functions we can only go up to the 8th derivative.
template <class T> LinearODE<T>::LinearODE(){
	a = 0.0;
	b = 1.0;
	form = "NORMAL";
	I0 = 0.0;
}
template <class T> LinearODE<T>::LinearODE(int k){
	order = k;
	a = 0.0;
	b = 1.0;
	I0 = 0.0;
	form = "NORMAL";
}
template <class T> string LinearODE<T>::toString(){
	string out = "ODE of ";
	out = out + to_string(order) + "-th order defined on the interval (";
	out = out+to_string(a)+","+to_string(b)+")";
	return out;
}
template <class T> void LinearODE<T>::setDomain(double c, double d){
	a = c;
	b = d;
}
template <class T> void LinearODE<T>::setCoefficient(int i,std::function<T(T)> f){
	K[i] = f;
}
template <class T> void LinearODE<T>::setIC(T y0){
	I0 = y0;
}
template <class T> std::tuple<std::vector<T>,std::vector<T>> LinearODE<T>::ScalarEuler(T h){
	T data;
	assert(form == "NORMAL" && "Error: ODE must be in normal form.");
	assert(order == 1 && "Error: Euler method only work for dy/dt.");	
	int N = int((b-a)/h);
	std::vector<T> timesteps = {I0};	
	std::vector<double> domain = {a};
	for (int i=1;i<N;i++){
		data = (-K[1](i*h)*timesteps[i-1]-K[0](i*h))*h;
		timesteps.push_back(timesteps[i-1]+data);
		domain.push_back(a+i*h);
	}
	return std::make_tuple(domain,timesteps);
}

