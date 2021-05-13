#ifndef ROOTHEADDEF
#define ROOTHEADDEF
#include "../suite.hpp"
#include <iostream>
#include <functional>
#include <vector>

double Newton(std::function<double(double)> f, std::function <double(double)> df,double x0,int itmax, double tol, int m);
double AutoNewton(std::function<double(double)> f, double h,double x0,int Nmax, double tol, int m);

#endif
