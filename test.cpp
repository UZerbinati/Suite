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
	ComplexFlag = true;
	DiffFlag = true;

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

	std::cout << "Testing auto-differentation library [ ]" << std::endl;
	Diff df(f);
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
	return 0;
}
