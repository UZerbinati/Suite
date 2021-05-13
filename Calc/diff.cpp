#include <cmath>
#include "diff.hpp"

double dummy(double x){
	return 0;
}
Diff::Diff(){
	f = dummy;
	h = 0.001;
	type="forward";
}

double Diff::call(double x){
	double value;
	value = 0.0;
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
void Diff::push(std::function<double(double)> g){
	f = g;	
}
void Diff::set_h(double step){
	h = step;
}
void Diff::set_type(string fd){
	type = fd;
}
