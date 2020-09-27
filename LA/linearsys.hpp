#ifndef LINEARSYSHEADERDEF
#define LINEARSYSHEADERDEF
#include <iostream>
#include <string>

class LinSys
{
	private:
		mat *A;
		vec *b;
		std::string type;
		int *P;
	public:
		LinSys(mat &M, vec &v);
		vec BackSub();
		std::string toString();
		mat getMatrix();
		void setType(std::string value);
		void Gauss(int pivoting);

};

#endif
