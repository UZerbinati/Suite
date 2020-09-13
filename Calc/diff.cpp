#include <cmath>
#include "diff.hpp"

Diff::Diff(double (*g)(double x)){
	f = g;
	h = 0.001;
	type="forward";
}
double Diff::call(double x){
	double value;
	if(type ==  "forward"){
		value= (1/h)*(f(x+h)-f(x));
	}
	if(type == "backward"){
		value=(1/h)*(f(x)-f(x-h));
	}
	if(type == "centered"){
		value=(1/(2*h))*(f(x+h)-f(x-h)); 
	}
	return value;
}
