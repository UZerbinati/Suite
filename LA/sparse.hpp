#ifndef SPMATRIXHEADERDEF
#define SPMATRIXHEADERDEF

#include <cassert>
#include <string>

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
		double& operator()(unsigned i, unsigned j);
		void setItem(int *idx,int size, double data);
		double& getItem(int *idx, int size);
		std::string toString();
};

#endif
