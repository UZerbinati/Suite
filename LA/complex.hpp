#ifndef COMPLEXHEADERDEF
#define COMPLEXHEADERDEF

#include <iostream>

class Complex
{
	private:
		double real;
		double imag;
	public:
		Complex();
		Complex(double x, double y);
		void polar(double rho,double phi);
		double abs() const;
		double arg() const;
		double Real() const;
		double Imag() const;
		Complex pow(double n) const;
		Complex& operator= (const Complex& z);
		Complex operator+(const Complex& z) const;
		Complex operator-(const Complex& z) const;
		bool operator== (const Complex& other) const;
		friend std::ostream& operator<<(std::ostream& output, const Complex& z);
};

#endif
