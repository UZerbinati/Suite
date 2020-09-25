#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF

#include <cassert>
#include <string>
class mat
{
	private:
		int height;
		int width;
		double *data;
	public:
		mat(int n,int m);
		~mat();
		int getHeight();
		int getWidth();
		double& operator() (unsigned i, unsigned j);
		double& getItem(int *idx, int size);
		void setItem(int *idx,int size, double value);
		std::string toString();
		void from_Array(double *array, int size);
		mat& operator=(const mat &A);
		mat operator+(const mat &A) const;
		mat operator-(const mat &A) const;
		mat operator*(const double lam) const;
		void free();
};
#endif
