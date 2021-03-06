#include "../suite.hpp"
#include "ode.hpp"
#include <functional>
#include <vector>

using namespace std;

//Due to the way we initzialize the array of functions we can only go up to the 8th derivative.
template <class T> LinearODE<T>::LinearODE(){
	a = 0.0;
	b = 1.0;
	form = "NORMAL";
}
LinearODE<vec>::LinearODE(){
	a = 0.0;
	b = 1.0;
	form = "NORMAL";
}
template <class T> LinearODE<T>::LinearODE(int k){
	order = k;
	a = 0.0;
	b = 1.0;
	form = "NORMAL";
}
LinearODE<vec>::LinearODE(int k){
	order = k;
	a = 0.0;
	b = 1.0;
	form = "NORMAL";
}
template <class T> string LinearODE<T>::toString(){
	string out = "ODE of ";
	out = out + to_string(order) + "-th order defined on the interval (";
	out = out+to_string(a)+","+to_string(b)+")";
	return out;
}
string LinearODE<vec>::toString(){
	string out = "Linear ODE of ";
	out = out + to_string(order) + "-th order defined on the interval (";
	out = out+to_string(a)+","+to_string(b)+")";
	return out;
}
template <class T> void LinearODE<T>::setDomain(double c, double d){
	a = c;
	b = d;
}
void LinearODE<vec>::setDomain(double c, double d){
	a = c;
	b = d;
}
template <class T> void LinearODE<T>::setCoefficient(int i,std::function<T(double)> f){
	K[i] = f;
}
void LinearODE<vec>::setCoefficient(int i,std::function<spmat(double)> f){
	K[i] = f;
}
template <class T> void LinearODE<T>::setIC(std::vector<T> y0){
	I0=y0;
}
void LinearODE<vec>::setIC(std::vector <vec> y0){
	I0 = y0;
}
template <class T> std::tuple<std::vector<double>,std::vector<T>> LinearODE<T>::ScalarEuler(double h){
	T data;
	assert(form == "NORMAL" && "Error: ODE must be in normal form.");
	assert(order == 1 && "Error: Euler method only work for dy/dt.");	
	int N = int((b-a)/h);
	std::vector<T> timesteps = {I0};	
	std::vector<double> domain = {a};
	for (int i=1;i<N;i++){
		data = ((-1)*K[1](i*h)*timesteps[i-1])*h;
		data = data + ((-1)*K[0](i*h))*h;
		timesteps.push_back(timesteps[i-1]+data);
		domain.push_back(a+i*h);
	}
	return std::make_tuple(domain,timesteps);
}

std::tuple<std::vector<double>,std::vector<vec>> LinearODE<vec>::ScalarEuler(double h){
	// MU'(t)+KU(t)=0
	// MU'(t) = -KU(t);
	// U'(t) = M^{-1}(-kU(t))=data;
	// U(t+h)=U(t)+ data*h
	int N = int((b-a)/h);
	
	vec x0 (I0[0].getLen());
	vec data(I0[0].getLen());
	vec x(I0[0].getLen());
	vec one(I0[0].getLen());
	for (int k=0; k < data.getLen(); k++){
		data.setData(I0[0].getData(k),k);
		x0.setData(I0[0].getData(k),k);
		one.setData(1.0,k);
	}
	assert(form == "NORMAL" && "Error: ODE must be in normal form.");
	assert(order == 1 && "Error: Euler method only work for dy/dt.");	
	
	vec nadd(I0[0].getLen());

	std::vector<vec> timesteps = {};
	timesteps.push_back(nadd+data);	
	std::vector<double> domain = {a};

	

	for (int i=1;i<N;i++){
		data = (K[1](i*h)*timesteps[i-1]);
		data = data*(-1);
		data = (K[0](i*h)*one+data);
		spmat M(I0[0].getLen(),I0[0].getLen());
		M = K[2](i*h);
		if (solver == "JACOBI"){
			x = Jacobi(M,data,x0,solverIT,1e-8);
		}else if(solver == "GAUBSEIDEL"){
			x = GauBSeidel(M,data,x0,solverIT,1e-8);
		}else if(solver == "CG"){
			x = ConjugateGradient(M,data,x0,solverIT,1e-8);
		}	
		timesteps.push_back(timesteps[i-1]+x*(h));
		domain.push_back(a+i*h);
	}
	return std::make_tuple(domain,timesteps);
}
template <class T> void LinearODE<T>::setSolver(string stype, int sIT){
	solver = stype;
	solverIT = sIT;
}
void LinearODE<vec>::setSolver(string stype, int sIT){
	solver = stype;
	solverIT = sIT;
}
template <class T> NonLinearODE<T>::NonLinearODE(){
}
NonLinearODE<vec>::NonLinearODE(){
}
template <class T >NonLinearODE<T>::NonLinearODE(int k){
	order = k;
}
NonLinearODE<vec>::NonLinearODE(int k){
	order = k;
}
template <class T> string NonLinearODE<T>::toString(){
	string out = "Non Linear ODE of ";
	out = out + to_string(order) + "-th order defined on the interval (";
	out = out+to_string(a)+","+to_string(b)+")";
	return out;

}
string NonLinearODE<vec>::toString(){
	string out = "Non Linear ODE of ";
	out = out + to_string(order) + "-th order defined on the interval (";
	out = out+to_string(a)+","+to_string(b)+")";
	return out;
}
template <class T> void NonLinearODE<T>::setDomain(double c,double d){
	a = c; b=d;
	form = "NORMAL";
}
void NonLinearODE<vec>::setDomain(double c,double d){
	a = c; b=d;
	form = "NORMAL";
}
template <class T> void NonLinearODE<T>::setIC(std::vector<T> y0){
	I0 = y0;
}
void NonLinearODE<vec>::setIC(std::vector<vec> y0){
	I0 = y0;
}
template <class T> void NonLinearODE<T>::setSolver(std::string stype, int sIT){
	solver = stype;
	solverIT = sIT;	
}
void NonLinearODE<vec>::setSolver(string stype,int sIT){
	solver = stype;
	solverIT = sIT;
};
template <class T> void NonLinearODE<T>::setCoefficients(std::function<T(double)> m,std::function<T(std::vector<T>,double)> k){
	M = m;
	K = k;
}
void NonLinearODE<vec>::setCoefficients(std::function<spmat(double)> m, std::function<vec(std::vector<vec>,double)> k){
	M = m;
	K = k;	
}
template <class T> std::tuple<std::vector<double>, std::vector<T>> NonLinearODE<T>::Euler(double h){
	/*	| MEMENTO | Euler method only solves first order ODE.
	 *	f: T x R -> T
	 *	m(t)dy/dx = f(y,t)
	 *	m(t)dy = f(y,t)dx 
	 *	dy = (dx/m(t))*f(y,t)
	 */
	T data;
	assert(form == "NORMAL" && "Error: ODE must be in normal form.");
	assert(order == 1 && "Error: Euler method only work for dy/dt.");	
	int N = int((b-a)/h);
	std::vector<T> timesteps = {I0};	
	std::vector<double> domain = {a};
	std::vector<T> P;
	for (int i=1;i<N;i++){
		P = {timesteps[i-1]};
		data = K(P,i*h)*h;
		data = (1/M(i*h))*data;
		timesteps.push_back(timesteps[i-1]+data);
		domain.push_back(a+i*h);
	}
	return std::make_tuple(domain,timesteps);

}
std::tuple<std::vector<double>, std::vector<vec>> NonLinearODE<vec>::ImplicitEuler(double h, int fixIT){
	/*	| MEMENTO | Euler method only solves first order ODE.
	 *	f: T x R -> T
	 *	m(t)dy/dx = f(y,t)
	 *	m(t)dy = f(y,t)dx 
	 *	dy = (dx/m(t))*f(y,t)
	 */
	vec data(I0[0].getLen());
	vec x0 (I0[0].getLen());
	x0 = I0[0];
	assert(form == "NORMAL" && "Error: ODE must be in normal form.");
	assert(order == 1 && "Error: Euler method only work for dy/dt.");	
	int N = int((b-a)/h);
	std::vector<vec> timesteps = {x0};	
	std::vector<double> domain = {a};
	std::vector<vec> P;
	spmat A (I0[0].getLen(),I0[0].getLen());
	for (int i=1;i<N;i++){
		A = M(i*h);
		P = {timesteps[i-1]};
		data = K(P,i*h)*h;
		if (solver == "JACOBI"){
			data = Jacobi(A,data,x0,solverIT,1e-8);
		}else if(solver == "GAUBSEIDEL"){
			data = GauBSeidel(A,data,x0,solverIT,1e-8);
		}else if(solver == "CG"){
			data = ConjugateGradient(A,data,x0,solverIT,1e-8);
		}	
		timesteps.push_back(timesteps[i-1]+data);
		domain.push_back(a+i*h);
	}
	timesteps[0] = I0[0];
	return std::make_tuple(domain,timesteps);

}
std::tuple<std::vector<double>, std::vector<vec>> NonLinearODE<vec>::Euler(double h){
	/*	| MEMENTO | Euler method only solves first order ODE.
	 *	f: T x R -> T
	 *	m(t)dy/dx = f(y,t)
	 *	m(t)dy = f(y,t)dx 
	 *	dy = (dx/m(t))*f(y,t)
	 */
	vec data(I0[0].getLen());
	vec x0 (I0[0].getLen());
	x0 = I0[0];
	assert(form == "NORMAL" && "Error: ODE must be in normal form.");
	assert(order == 1 && "Error: Euler method only work for dy/dt.");	
	int N = int((b-a)/h);
	std::vector<vec> timesteps = {x0};	
	std::vector<double> domain = {a};
	std::vector<vec> P;
	spmat A (I0[0].getLen(),I0[0].getLen());
	for (int i=1;i<N;i++){
		A = M(i*h);
		P = {timesteps[i-1]};
		data = K(P,i*h)*h;
		if (solver == "JACOBI"){
			data = Jacobi(A,data,x0,solverIT,1e-8);
		}else if(solver == "GAUBSEIDEL"){
			data = GauBSeidel(A,data,x0,solverIT,1e-8);
		}else if(solver == "CG"){
			data = ConjugateGradient(A,data,x0,solverIT,1e-8);
		}	
		timesteps.push_back(timesteps[i-1]+data);
		domain.push_back(a+i*h);
	}
	timesteps[0] = I0[0];
	return std::make_tuple(domain,timesteps);

}
std::tuple<std::vector<double>, std::vector<vec>> NonLinearODE<vec>::SympEuler(double h){
	/*	| MEMENTO | Euler method only solves first order ODE.
	 *	f: T x R -> T
	 *	m(t)dy/dx = f(y,t)
	 *	m(t)dy = f(y,t)dx 
	 *	dy = (dx/m(t))*f(y,t)
	 */
	vec data(I0[0].getLen());
	vec x0 (I0[0].getLen());
	x0 = I0[0];
	data = I0[0];
	assert(form == "NORMAL" && "Error: ODE must be in normal form.");
	assert(order == 1 && "Error: Euler method only work for dy/dt.");	
	int N = int((b-a)/h);
	std::vector<vec> timesteps = {x0};	
	std::vector<double> domain = {a};
	std::vector<vec> P;
	spmat A (I0[0].getLen(),I0[0].getLen());

	for (int i=1;i<N;i++){
		A = M(i*h);
		P = {timesteps[i-1]};
		for (int k=1;k<I0[0].getLen();k++){
			auto implf = [i,P,k,h,K=this->K](double xi) { 
				std::cout << "i: "<< i << ", k: "<< k << std::endl;
				std::vector<vec> Q;
				Q = P;
				Q[0].setData(xi,k-1);	
				std::cout << "xi: " << xi << std::endl;
				std::cout << "Q: " << Q[0].toString() << std::endl;
				std::cout << "f("<<xi<<")"<< xi-P[0].getData(k-1)-K(Q,i*h).getData(k-1)*h << std::endl;
				return xi-P[0].getData(k-1)-K(Q,i*h).getData(k-1)*h;
			};	
			data.setData(AutoNewton(implf,0.1*h,data.getData(k-1),20,1e-8,1),k-1);
			//data.setData(K(P,i*h).getData(k-1)*h,k-1);
			
		}
		data.setData(timesteps[i-1].getData(I0[0].getLen()-1)+K(P,i*h).getData(I0[0].getLen()-1)*h,I0[0].getLen()-1);
		//data = K(P,i*h)*h;
		if (solver == "JACOBI"){
			data = Jacobi(A,data,x0,solverIT,1e-8);
		}else if(solver == "GAUBSEIDEL"){
			data = GauBSeidel(A,data,x0,solverIT,1e-8);
		}else if(solver == "CG"){
			data = ConjugateGradient(A,data,x0,solverIT,1e-8);
		}	
		timesteps.push_back(data);
		domain.push_back(a+i*h);
	}
	timesteps[0] = I0[0];
	return std::make_tuple(domain,timesteps);

}
std::tuple<std::vector<double>, std::vector<vec>> NonLinearODE<vec>::RK(double h,int RKOrder){
	/*	| MEMENTO | We here implement a Runge-Kutta method to 
	 *	            solves first order ODE.
	 *	f: T x R -> T
	 *	m(t)dy/dx = f(y,t)
	 *	dy = dx*f(u(t)+0.5dxf(u(t)))
	 */
	vec data(I0[0].getLen());
	vec x0 (I0[0].getLen());
	x0 = I0[0];
	assert(form == "NORMAL" && "Error: ODE must be in normal form.");
	assert(order == 1 && "Error: RK method only work for dy/dt.");	
	int N = int((b-a)/h);
	std::vector<vec> timesteps = {x0};	
	std::vector<double> domain = {a};
	std::vector<vec> P;
	std::vector<vec> k1;
	spmat A (I0[0].getLen(),I0[0].getLen());
	for (int i=1;i<N;i++){
		A = M(i*h);
		P = {timesteps[i-1]};
		if (RKOrder==2){
			k1 = {timesteps[i-1]+K(P,i*h)*0.5*h};
			data = K(k1,(i+0.5)*h)*h;
		}
		if (solver == "JACOBI"){
			data = Jacobi(A,data,x0,solverIT,1e-8);
		}else if(solver == "GAUBSEIDEL"){
			data = GauBSeidel(A,data,x0,solverIT,1e-8);
		}else if(solver == "CG"){
			data = ConjugateGradient(A,data,x0,solverIT,1e-8);
		}	
		timesteps.push_back(timesteps[i-1]+data);
		domain.push_back(a+i*h);
	}
	timesteps[0] = I0[0];
	return std::make_tuple(domain,timesteps);

}
