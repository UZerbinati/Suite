#ifndef SPMATRIXHEADERDEF
#define SPMATRIXHEADERDEF

#include <cassert>
#include <string>
#include <vector>

class spmat
{
	private:
		int height;
		int width;
		double *value;
		int* P;
		int p;
	public:
		spmat(int n,int m);
		spmat();
		~spmat();
		int getWidth();
		int getHeight();
		int getSize();
		void empty();
		double& operator()(int i, int j);
		double& getData(int i,int j);
		void setItem(int *idx,int size, double data);
		double& getItem(int *idx, int size);
		friend vec operator*(const spmat &M, const vec &v);
		friend spmat operator+(spmat A,spmat B);
		friend spmat operator*(const double lambda, spmat A);
		std::string toString();
};
vec operator*(const spmat &M, const vec &v);
spmat operator*(const double lambda, spmat A);
spmat operator+(spmat A,spmat B);
#endif
