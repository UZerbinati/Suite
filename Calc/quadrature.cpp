#include "../suite.hpp"
#include "quadrature.hpp"

double NewtonCotes(MeshFunction f,double h,int order){
	if(f.getDim()[0]==1 and f.getDim()[1]==1){
		std::cout << "INSIDE" << std::endl;
		double a = f.getLineEx()[0];
		double b = f.getLineEx()[1];
		int N = int((b-a)/h);
		std::vector <double> P;
		N = N+1; //We fix a bigger N to have the size of the quadrature elements always smaller then h.
		double delta = (b-a)/N;
		double S=0.0;
		std::cout << "a: " << a<< ", b: "<< b << std::endl;
		for(int k=0; k<N; k++){
			if (order == 0){
				std::cout << "order 0" << std::endl;
				P = {a+k*delta+0.5*delta};
				S = S+delta*f.eval(P,1)[0];
			}else if(order == 1){
				P = {a+k*delta};
				S = S+(0.5*delta*f.eval(P,1)[0]);
				P = {a+((k+1)*delta)};
				S = S+(0.5*delta*f.eval(P,1)[0]);
			}
		}
		return S;
	}
}
std::vector <double> Integrate(MeshFunction f,Mesh mesh){
	std::vector <double> S;
	double value;
	if (f.getDim()[1] == 1){
		if (mesh.getType()=="UNIFORM"){
			value = NewtonCotes(f,mesh.getSize(0),1);	
		}
		S.push_back(value);
	}
	return S;	
}
