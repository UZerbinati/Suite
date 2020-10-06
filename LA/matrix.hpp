#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF

#include <cassert>
#include <string>

class mat
{
	private:
		int height;
		int width;
		bool parallel;
		double *data;
	public:
		mat(int n,int m);
		mat();
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
		friend vec operator*(const mat &M,const vec &v);
		void free();
		void SetParallel(bool set);
		bool GetParallel();
};
		vec operator*(const mat &M,const vec &v);
#endif
