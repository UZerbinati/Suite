#include "1D.hpp"
#include <string>

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

Mesh::Mesh(int n){
	dim = n;
}
void Mesh::UniformMesh(line I, double h){
	N = int((I.getPoint(1)-I.getPoint(0))/h);	
	for (int i=0; i < N; i++){
		line l(I.getPoint(0)+i*h,I.getPoint(0)+(i+1)*h);
		lineElements.push_back(l);
	}
}
std::string Mesh::toString(){
	std::string out;
	out = "";
	if (dim == 1){
		out = "|1D Mesh|\n";
		out = out + "Mesh made by "+std::to_string(N)+".\n";
		for (int i=0;i<N;i++){
			out = out+"("+std::to_string(lineElements[i].getPoint(0))+","+std::to_string(lineElements[i].getPoint(1))+")\n";
		}
	}
	return out;
}
