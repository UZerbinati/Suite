#include <cmath>
#include <string>
#include "complex.hpp"


//Override the default constructor

/*Complex::Complex()
{
	real = 0.0;
	imag = 0.0;
}*/

//Constructor that assign the value to the complex number as z=x+iy
Complex::Complex(double x,double y)
{
	real = x;
	imag = y;
}

//Adding method to define a complex number by polar coordinate
void Complex::polar(double rho,double phi)
{
	real = rho*cos(phi);
	imag = rho*sin(phi); 
}

//Adding a method to compute the real part of a  complex number
double Complex::Real() const
{
	return real;
}
//Adding a method to compute the imaginary part of a  complex number
double Complex::Imag() const
{
	return imag;
}
//Adding a method to compute the abs (i.e. norm 2) of a complex number
double Complex::abs() const
{
	return sqrt(real*real+imag*imag);
}

//Adding a method to compute the argument of a complex number
double Complex::arg() const
{
	return atan2(imag,real);
}

//Adding a method to compute the power of a complex number

Complex Complex::pow(double n) const
{
	double rho;
	double phi;

	rho = abs();
	phi = arg();
	
	Complex z(0,0);
	z.polar(std::pow(rho,n),n*phi);
	return z;
}

//Override subtraction operator

Complex Complex::operator-(const Complex& z) const
{
	Complex w(0,0);

	w.real = real - z.real;
	w.imag = imag - z.imag;

	return w;
}

//Override adding operator

Complex Complex::operator+(const Complex& z) const
{
	Complex w(0,0);

	w.real = real + z.real;
	w.imag = imag + z.imag;

	return w;
}

//Override equal operator

Complex& Complex::operator=(const Complex& z)
{
	real = z.real;
	imag = z.imag;

	return *this;
}
//Override == operator
bool Complex::operator==(const Complex& other) const
{
	bool flag;
	if (real == other.real){
		flag = true;
	}else{
		flag = false;
	}

	if (imag == other.imag){
		flag = flag && true;
	}else{
		flag = flag && false;
	}

	return flag;
}
//Override print operator

std::ostream& operator<< (std::ostream& output, const Complex& z) 
{
	output << "(" << z.real << ", " << z.imag << "i)";
}
//to String function
std::string Complex::toString() const
{
	std::string str = "("+std::to_string(real)+","+std::to_string(imag)+")";
	return str;
}
