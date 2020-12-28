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
}
LinearODE<vec>::LinearODE(){
	a = 0.0;
	b = 1.0;
	form = "NORMAL";
}
template <class T> LinearODE<T>::LinearODE(int k){
	order = k;
	a = 0.0;
	b = 1.0;
	form = "NORMAL";
}
LinearODE<vec>::LinearODE(int k){
	order = k;
	a = 0.0;
	b = 1.0;
	form = "NORMAL";
}
template <class T> string LinearODE<T>::toString(){
	string out = "ODE of ";
	out = out + to_string(order) + "-th order defined on the interval (";
	out = out+to_string(a)+","+to_string(b)+")";
	return out;
}
string LinearODE<vec>::toString(){
	string out = "ODE of ";
	out = out + to_string(order) + "-th order defined on the interval (";
	out = out+to_string(a)+","+to_string(b)+")";
	return out;
}
template <class T> void LinearODE<T>::setDomain(double c, double d){
	a = c;
	b = d;
}
void LinearODE<vec>::setDomain(double c, double d){
	a = c;
	b = d;
}
template <class T> void LinearODE<T>::setCoefficient(int i,std::function<T(double)> f){
	K[i] = f;
}
void LinearODE<vec>::setCoefficient(int i,std::function<spmat(double)> f){
	K[i] = f;
}
template <class T> void LinearODE<T>::setIC(T y0){
	I0 = y0;
}
void LinearODE<vec>::setIC(vec y0){
	I0 = new vec(y0.getLen());
	*I0 = y0;
}
template <class T> std::tuple<std::vector<double>,std::vector<T>> LinearODE<T>::ScalarEuler(double h){
	T data;
	assert(form == "NORMAL" && "Error: ODE must be in normal form.");
	assert(order == 1 && "Error: Euler method only work for dy/dt.");	
	int N = int((b-a)/h);
	std::vector<T> timesteps = {I0};	
	std::vector<double> domain = {a};
	for (int i=1;i<N;i++){
		data = ((-1)*K[1](i*h)*timesteps[i-1])*h;
		data = data + ((-1)*K[0](i*h))*h;
		timesteps.push_back(timesteps[i-1]+data);
		domain.push_back(a+i*h);
	}
	return std::make_tuple(domain,timesteps);
}

std::tuple<std::vector<double>,std::vector<vec>> LinearODE<vec>::ScalarEuler(double h){
	int N = int((b-a)/h);

	vec data(I0->getLen());
	for (int k=0; k < data.getLen(); k++){
		data.setData(I0->getData(k),k);
	}
	assert(form == "NORMAL" && "Error: ODE must be in normal form.");
	assert(order == 1 && "Error: Euler method only work for dy/dt.");	
	
	vec nadd(I0->getLen());

	std::vector<vec> timesteps = {};
	timesteps.push_back(nadd+data);	
	std::vector<double> domain = {a};

	
	for (int i=1;i<N;i++){
		data = (K[0](i*h)*timesteps[i-1]);
		data = data*(-h);
		timesteps.push_back(timesteps[i-1]+data);
		domain.push_back(a+i*h);
	}
	return std::make_tuple(domain,timesteps);
}
