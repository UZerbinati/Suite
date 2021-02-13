#include "../suite.hpp"
#include "1D.hpp"
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>

line::line(){
	a = 0.0;
	b = 1.0;
}
line::line(double c, double d){
	a = c;
	b = d;
}
double line::getPoint(int k){
	if (k == 0){
		return a;
	}else if (k==1){
		return b;
	}
}
Mesh::Mesh(){
	dim = 1;
}
Mesh::Mesh(int n){
	dim = n;
}
int Mesh::getDimension(){
	return dim;
}
double Mesh::getSize(int k){
	return H[k];
}
void Mesh::UniformMesh(line I, double h){
	type = "UNIFORM";
	N = int((I.getPoint(1)-I.getPoint(0))/h);	
	if ((I.getPoint(1)-I.getPoint(0))-(N-1)*h == 0){
	       N = N-1;
	}	       
	for (int i=0; i < N; i++){
		line l(I.getPoint(0)+i*h,I.getPoint(0)+(i+1)*h);
		lineElements.push_back(l);
		H.push_back(h);
		mesh_tol.push_back(0);
	}
	line l(I.getPoint(0)+N*h,I.getPoint(0)+(N+1)*h);
	lineElements.push_back(l);
	H.push_back(h);
	mesh_tol.push_back(0);
}
int Mesh::getElementNumber(){
	return N;
}
line Mesh::getLineElement(int k){
	return lineElements[k];	
}
double Mesh::getElementTollerance(int k){
	return mesh_tol[k];
}
std::string Mesh::toString(){
	std::string out;
	out = "";
	if (dim == 1){
		out = "|1D Mesh|\n";
		out = out + "Mesh made by "+std::to_string(N)+".\n";
		for (int i=0;i<N;i++){
			out = out+std::to_string(i)+". ";
			out = out+"["+std::to_string(lineElements[i].getPoint(0))+","+std::to_string(lineElements[i].getPoint(1))+"]\n";
		}
	}
	return out;
}
std::string Mesh::getType(){
	return type;
}
MeshFunction::MeshFunction(){
}
MeshFunction::MeshFunction(Mesh m, int n){
	mesh = m;
	dim = n;
}
void MeshFunction::pushFunction(std::function<std::vector<double>(std::vector<double>)> f){
	if (mesh.getDimension() == 1){
		std::vector<double> P;
	        P= {mesh.getLineElement(0).getPoint(0)};
		data.push_back(f(P));
		//std::cout << std::to_string(f(P)[0]) << std::endl;
		for (int k=0; k < mesh.getElementNumber(); k++){
			P = {mesh.getLineElement(k).getPoint(1)};
			data.push_back(f(P));
			//std::cout << std::to_string(k) << ". ("<< mesh.getElement(k).getPoint(0)-mesh.getElementTollerance(k)<< ","<< mesh.getElement(k).getPoint(1)+mesh.getElementTollerance(k)<< ") -> " << std::to_string(data[k+1][0]) << std::endl;
		}	
	}
}
std::vector <double> MeshFunction::eval(std::vector <double> P, int p){
	std::vector<double> value;
	bool flag1;
	bool flag2;
	bool flag3;
	double a;
	double b;
	if (mesh.getDimension()==1){
		for (int k=0; k < mesh.getElementNumber(); k++){
			a = mesh.getLineElement(k).getPoint(0)-mesh.getElementTollerance(k);
			b = mesh.getLineElement(k).getPoint(1)+mesh.getElementTollerance(k);
			flag1 = (P[0] >= a);
			flag2 = (P[0] < b);
			//std::cout << k << ". " << "point inside (" << std::to_string(flag1)<<"," <<std::to_string(flag2)<<")" << ", point value " << P[0]<< ", element ("<< a <<"," << b << ")" << std::endl;
			if (flag1 and flag2){
				if (p==0){
					return data[k];
				}else if (p==1){
						value = {(data[k+1][0]-data[k][0])/(b-a)*(P[0]-a)+data[k][0]};
						//std::cout << "data: (" << std::to_string(data[k+1][0]) <<"," << std::to_string(data[k][0])<< ") ; ("<< std::to_string(b)<<"," << std::to_string(a) << "); x=" << std::to_string(P[0]) << "value: " << std::to_string(value[0]) << std::endl;
						return value;
				}
			}
		}
		//std::cout << "Data: " << std::to_string(data[mesh.getElementNumber()][0])<< std::endl;
		return data[mesh.getElementNumber()]; 
	}
}
vec MeshFunction::export_vec(){
	vec v(mesh.getElementNumber()+1);
	if (dim==1){
		for (int k=0; k < mesh.getElementNumber()+1;k++){
			//std::cout << v.getData(k) << std::endl;
			v.setData(data[k][0],k);
		}
	}
	return v;

}
void MeshFunction::import_vec(vec &v){
	if (dim==1){
		for (int k=0; k < mesh.getElementNumber()+1;k++){
			//std::cout << v.getData(k) << std::endl;
			data[k][0] = v.getData(k);
		}
	}
}
std::vector <int> MeshFunction::getDim(){
	std::vector <int>ndim = {mesh.getDimension(),dim};
	return ndim;
}
std::vector <double> MeshFunction::getLineEx(){
	std::vector <double> Ex;
	Ex.push_back(mesh.getLineElement(0).getPoint(0));
	Ex.push_back(mesh.getLineElement(mesh.getElementNumber()-1).getPoint(1));
	return Ex;
}
std::string MeshFunction::toString(){
	std::string out = "Mesh function defined on: \n";
	out = out + mesh.toString();
	return out;
}
double MeshFunction::getSize(int k){
	return mesh.getSize(k);
}
double MeshFunction::norm(int p){
	double S;
	S = 0.0;
	for (int k=0; k < mesh.getElementNumber()+1; k++){
		if (dim==1){
			std::cout << "h: " << mesh.getSize(k) << ", data: " << std::abs(data[k][0]) << ", S: " << std::to_string(S) << "." << std::endl; 
			S = S + pow(std::abs(data[k][0]),p);	
		}
	}
	return pow(mesh.getSize(0)*S,1.0/p);	
}
BC::BC(){
	type = "UNSET";
}
BC::BC(std::string BCtype, MeshFunction BCf){
	type = BCtype;
	f = BCf;
}
vec BC::apply(vec v){ 
	int l;
	bool flag;
	l = v.getLen();
	vec w(l);
	vec vec_f(l);	
	w = v;
	vec_f = f.export_vec();
	flag = (f.getDim()[0] == 1) and (f.getDim()[1]==1);
	//std::cout << "(" << std::to_string(f.getDim()[0])<<"," << std::to_string(f.getDim()[1])<<")"<< "->" << flag << std::endl;
	if (flag){
		//std::cout << "v: " << v.toString() << " f: " << vec_f.toString() << std::endl;
		w.setData(vec_f.getData(0),0);
		w.setData(vec_f.getData(l-1),l-1);
	}
	return w;
}
vec BC::HOApply(vec v,std::vector<double> ghosts){ 
	int l;
	bool flag;
	l = v.getLen();
	vec w(l);
	vec vec_f(l);	
	w = v;
	vec_f = f.export_vec();
	flag = (f.getDim()[0] == 1) and (f.getDim()[1]==1);
	//std::cout << "(" << std::to_string(f.getDim()[0])<<"," << std::to_string(f.getDim()[1])<<")"<< "->" << flag << std::endl;
	if (flag){
		//std::cout << "v: " << v.toString() << " f: " << vec_f.toString() << std::endl;
		w.setData(vec_f.getData(0),0);
		w.setData(vec_f.getData(l-1),l-1);
	}
	if (flag){	
		if (ghosts.size()==2){
			w.setData(v.getData(1)+ghosts[0],1);
			w.setData(v.getData(l-2)+ghosts[1],l-2);
		}
	}
	return w;
}
MeshFunction* BC::get_function(){
	return &f;
}
std::string BC::get_Type(){
	return type;
}
std::vector <int> BC::getDim(){
	return f.getDim();
}

