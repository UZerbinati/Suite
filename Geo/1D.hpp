#ifndef ONEDGEOHEADREF
#define ONEDGEOHEADREF 
#include <iostream>
#include <string>
#include <vector>
class line
{
	private:
		double a;
		double b;
	public:
		line();
		line(double c, double d);
		double getPoint(int k);
};
class Mesh
{
	private:
		int dim;
		std::vector <line> lineElements;
		int N;
	public:
		Mesh(int n);
		void UniformMesh(line I,double h);
		std::string toString();
	

};
#endif

