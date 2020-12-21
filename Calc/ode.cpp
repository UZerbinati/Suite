#include "../suite.hpp"
#include "ode.hpp"
#include <functional>
#include <vector>

using namespace std;

//Due to the way we initzialize the array of functions we can only go up to the 8th derivative.
LinearODE::LinearODE(){
	a = 0.0;
	b = 1.0;
	form = "NORMAL";
	I0 = 0.0;
}
LinearODE::LinearODE(int k){
	order = k;
	a = 0.0;
	b = 1.0;
	I0 = 0.0;
	form = "NORMAL";
}
string LinearODE::toString(){
	string out = "ODE of ";
	out = out + to_string(order) + "-th order defined on the interval (";
	out = out+to_string(a)+","+to_string(b)+")";
	return out;
}
void LinearODE::setDomain(double c, double d){
	a = c;
	b = d;
}
void LinearODE::setCoefficient(int i,std::function<double(double)> f){
	K[i] = f;
}
void LinearODE::setIC(double y0){
	I0 = y0;
}
std::tuple<std::vector<double>,std::vector<double>> LinearODE::ScalarEuler(double h){
	double data;
	assert(form == "NORMAL" && "Error: ODE must be in normal form.");
	assert(order == 1 && "Error: Euler method only work for dy/dt.");	
	int N = int((b-a)/h);
	std::vector<double> timesteps = {I0};	
	std::vector<double> domain = {a};
	for (int i=1;i<N;i++){
		data = (-K[1](i*h)*timesteps[i-1]-K[0](i*h))*h;
		timesteps.push_back(timesteps[i-1]+data);
		domain.push_back(a+i*h);
	}
	return std::make_tuple(domain,timesteps);
}

