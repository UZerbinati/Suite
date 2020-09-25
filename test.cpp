#include <iostream>
#include <cmath>
#include "suite.hpp"

double f(double x)
{
	return 2*x;
}


int main()
{
	std::cout << "----------------------" << std::endl << "| Testing SUITE |" << std::endl << "----------------------" <<std::endl;
	std::cout << "Testing complex number library [ ]" << std::endl;
	Complex z(1,1);
	bool ComplexFlag;
	bool DiffFlag;
	bool VecFlag;
	ComplexFlag = true;
	DiffFlag = true;
	VecFlag = true;

	//ABS CHECK
	if (z.abs() == sqrt(2)){
		std::cout << "\t --abs [*]" << std::endl;
		ComplexFlag = ComplexFlag && true;
	}else{
		std::cout << "\t --abs [!]" << std::endl;
		ComplexFlag = ComplexFlag && false;
	}
	//COMPLEX SUM CHECK
	Complex w(1,1);
	if ((z+w).abs() == sqrt(8)){
		std::cout << "\t --complex sum  [*]" << std::endl;
		ComplexFlag = ComplexFlag && true;
	}else{

		std::cout << "\t --complex sum  [!]" << std::endl;
		ComplexFlag = ComplexFlag && false;
	}
	//EQUAL CHECK
	if (z==w){
		std::cout << "\t --complex comparison  [*]" << std::endl;
		ComplexFlag = ComplexFlag && true;
	}else{

		std::cout << "\t --complex comparison  [!]" << std::endl;
		ComplexFlag = ComplexFlag && false;
	}
	//POW CHECK
	Complex rho(0,1);
	if ((rho.pow(2)).Real() == -1 && (rho.pow(2)).Imag() <= 2e-16){
		std::cout << "\t --complex power  [*]" << std::endl;
		ComplexFlag = ComplexFlag && true;
	}else{

		std::cout << "\t --complex power  [!]" << std::endl;
		ComplexFlag = ComplexFlag && false;
	}
	if (ComplexFlag){
		std::cout << "Testing complex number library [*]" << std::endl;
	}else{
		std::cout << "Testing complex number library [!]" << std::endl;
	}

	std::cout << std::endl << "Testing auto-differentation library [ ]" << std::endl;
	Diff df;
	df.push(f);
	//FINITE DIFFERENCE CHECK
	if (int(df.call(0.1)) == int(2)){
		DiffFlag = DiffFlag && true;
		std::cout << "\t --forward finite difference of a constant  [*]" << std::endl;
	}else{
		std::cout << "\t --forward finite difference of a constant  [!]" << std::endl;
		DiffFlag = DiffFlag && false;
	}
	if (DiffFlag){
		std::cout << "Testing auto-differentiation library [*]" << std::endl;
	}else{
		std::cout << "Testing auto-differentiation library [!]" << std::endl;
	}

	std::cout << std::endl << "Testing vector-matrix library [ ]" << std::endl;
	vec v(3); v[1] = 1; v[2] = 2; v[3] = 1;
	if (int(v[-1]) == int(v[3])){
		VecFlag = VecFlag && true;
		std::cout << "\t --negative indexing  [*]" << std::endl;
	}else{
		std::cout << "\t --negative indexing  [!]" << std::endl;
		VecFlag = VecFlag && false;
	}
	vec a(3); a = v;
	if (int(a[3]) == int(v[3])){
		VecFlag = VecFlag && true;
		std::cout << "\t --assignment of vector value [*]" << std::endl;
	}else{
		std::cout << "\t --assignment of vector value [!]" << std::endl;
		VecFlag = VecFlag && false;
	}
	vec  b(3); b = a+v;
	/*
	std::cout << b[1] << "," << b[2] << "," << b[3] << std::endl;
	std::cout << a[1] << "," << a[2] << "," << a[3] << std::endl;
	std::cout << v[1] << "," << v[2] << "," << v[3] << std::endl;
	*/
	if (int(b[3]) == int(a[3])+int(v[3])){
		VecFlag = VecFlag && true;
		std::cout << "\t --sum vector operation [*]" << std::endl;
	}else{
		std::cout << "\t --sum vector operation [!]" << std::endl;
		VecFlag = VecFlag && false;
	}
	vec  c(3); c = a-v;
	if (int(c[3]) == int(a[3])-int(v[3])){
		VecFlag = VecFlag && true;
		std::cout << "\t --subtraction vector operation [*]" << std::endl;
	}else{
		std::cout << "\t --subtraction vector operation [!]" << std::endl;
		VecFlag = VecFlag && false;
	}


	mat M(3,3);
	M(1,1) = 1; M(2,2) = 2; M(3,3)=3;
	std::cout << "("<< M.getHeight() << "," << M.getWidth() << ")" << std::endl;
	std::cout << M.toString() << std::endl;
	return 0;
}
