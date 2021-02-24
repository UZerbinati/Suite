#ifndef ONEDGEOHEADREF
#define ONEDGEOHEADREF 
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "2D.hpp"

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
		std::vector <Square> squareElements;
		int N;
		std::vector <double> Hx;
		std::vector <double> Hy;
		std::vector <double> mesh_tol;
		std::vector <double> Container;
		std::string type;
		double h;
	public:
		Mesh();
		Mesh(int n);
		void UniformMesh(line I,double h);
		void UniformSqMesh(std::vector<double> container,int k);
		int getDimension();
		int getElementNumber();
		line getLineElement(int k);
		Square getSquareElement(int k);
		double getElementTollerance(int k);
		double getSize(int k);
		std::string toString();
		std::string getType();
		std::vector<double> getContainer();	

};
class MeshFunction
{
	private:
		Mesh mesh;
		int dim;
		std::function <std::vector<double>(std::vector<double>)> F;
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
		double getSize(int k);
		double norm(int p);
		std::vector <double> getContainer();
};
class BC
{
	private:
		std::string type;  			Geometry geo;	
		MeshFunction f;
	public:
		BC();
		BC(std::string BCtype, MeshFunction BCf);
		BC(std::string BCtype, MeshFunction BCf,Geometry geo);
		Geometry getGeo();
		vec apply(vec v);
		vec HOApply(vec v,int order,std::string type, std::vector<double> ghosts);
		MeshFunction* get_function();
		std::string get_Type();
		std::vector <int> getDim();

};
#endif

