#include "1D.hpp"
#include <string>
#include <cmath>

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
	N = int((I.getPoint(1)-I.getPoint(0))/h)+1;	
	if (I.getPoint(1)-(N-1)*h == 0){
	       N = N-1;
	}	       
	for (int i=0; i < N; i++){
		line l(I.getPoint(0)+i*h,I.getPoint(0)+(i+1)*h);
		lineElements.push_back(l);
		H.push_back(h);
		mesh_tol.push_back(h/10);
	}
	line l(I.getPoint(0)+N*h,I.getPoint(0)+(N+1)*h);
	lineElements.push_back(l);
	H.push_back(h);
	mesh_tol.push_back(h/10);
}
int Mesh::getElementNumber(){
	return N;
}
line Mesh::getElement(int k){
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
MeshFunction::MeshFunction(Mesh m, int n){
	mesh = m;
	dim = n;
}
void MeshFunction::pushFunction(std::function<std::vector<double>(std::vector<double>)> f){
	if (mesh.getDimension() == 1){
		std::vector<double> P;
	        P= {mesh.getElement(0).getPoint(0)};
		data.push_back(f(P));
		for (int k=0; k < mesh.getElementNumber(); k++){
			P = {mesh.getElement(k).getPoint(1)};
			data.push_back(f(P));
			//std::cout << std::to_string(k) << ". ("<< mesh.getElement(k).getPoint(0)-mesh.getElementTollerance(k)<< ","<< mesh.getElement(k).getPoint(1)+mesh.getElementTollerance(k)<< ") -> " << std::to_string(data[k][0]) << std::endl;
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
			a = mesh.getElement(k).getPoint(0)-mesh.getElementTollerance(k);
			b = mesh.getElement(k).getPoint(1)+mesh.getElementTollerance(k);
			flag1 = (P[0] > a);
			flag2 = (P[0] < b);
			std::cout << k << ". " << "point inside (" << std::to_string(flag1)<<"," <<std::to_string(flag2)<<")" << ", point value " << P[0]<< ", element ("<< a <<"," << b << ")" << std::endl;
			if (flag1 and flag2){
				if (p==0){
					return data[k];
				}else if (p==1){
					value = {data[k][0]+(data[k+1][0]-data[k][0])/(b-a)*(P[0]-a)};
					return value;
				}
			}
		}
		return data[mesh.getElementNumber()-1]; 
	}
}
vec MeshFunction::export_vec(){
	if (dim==1){
		vec v(mesh.getElementNumber());
		for (int k=0; k < mesh.getElementNumber();k++){
			v.setData(data[k][0],k);
		}
		return v;
	}
}
void MeshFunction::import_vec(vec &v){
	if (dim==1){
		for (int k=0; k < mesh.getElementNumber();k++){
			std::cout << v.getData(k) << std::endl;
			data[k][0] = v.getData(k);
		}
	}
}

