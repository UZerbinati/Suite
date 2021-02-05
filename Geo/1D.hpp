#ifndef ONEDGEOHEADREF
#define ONEDGEOHEADREF 
#include <iostream>
#include <string>
#include <vector>
#include <functional>

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
		std::vector <double> H;
		std::vector <double> mesh_tol;
		std::string type;
	public:
		Mesh();
		Mesh(int n);
		void UniformMesh(line I,double h);
		int getDimension();
		int getElementNumber();
		line getLineElement(int k);
		double getElementTollerance(int k);
		double getSize(int k);
		std::string toString();
		std::string getType();
	

};
class MeshFunction
{
	private:
		Mesh mesh;
		int dim;
		std::vector <std::vector<double>> data;
	public:
		MeshFunction();
		MeshFunction(Mesh mesh,int n);
		void pushFunction(std::function<std::vector<double>(std::vector<double>)>);
		std::vector <double> eval(std::vector <double>,int p);
		std::vector <int> getDim();
		vec export_vec();
		void import_vec(vec &v);
		std::vector <double> getLineEx();
		std::string toString();
};
class BC
{
	private:
		std::string type;  		
		MeshFunction f;
	public:
		BC();
		BC(std::string BCtype, MeshFunction BCf);
		vec apply(vec v);
		spmat BoundaryOp();
		MeshFunction* get_function();
		std::string get_Type();
		std::vector <int> getDim();

};
#endif

