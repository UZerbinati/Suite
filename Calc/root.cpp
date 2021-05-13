#include "../suite.hpp"
#include "root.hpp"

double Newton(std::function<double(double)> f, std::function <double(double)> df,double x0,int itmax, double tol,int m){
	double x;
	x = x0;
	for (int k=0; k<itmax; k++){
		x0 = x;
		x = x - m*f(x)/df(x);	
		if (abs(x-x0)<tol){
			break;
		}
	}
	
	return x;
}

double AutoNewton(std::function<double(double)> f, double h,double x0,int Nmax, double tol,int m){
	double x;
	double df;
	x = x0;
	for (int k=0; k<Nmax; k++){
		/*x = x - (m*f(x)*2*h)/(f(x+h)-f(x-h));	
		if (abs((m*f(x)*2*h)/(f(x+h)-f(x-h)))<tol){
			break;
		}*/
		df = (0.5/h)*(f(x+h)-f(x-h));
		if (abs(df)<tol){
			x = x -m*(f(x)/tol);
		}else{
			x = x - m*(f(x)/df);
		}
	}
	
	return x;
}

