#include "../suite.hpp"
#include <omp.h>
#include <tuple>

//TODO Implement parallel Cholesky-Courant

std::tuple<mat,mat> ParallelGS(mat &A){
	//Init Q and R
	mat Q(A.getHeight(),A.getHeight());
	mat R(A.getWidth(),A.getWidth());
	//Computing Q first column
	vec a1(A.getHeight());
	a1 = A.getColumn(1);
	R(1,1)=a1.norm(2);
	vec q1(A.getHeight()); 
	q1 = a1*(1/a1.norm(2)); //q1 = normalized a1; 
	Q.pushColumn(q1,1);
	//Empty the memory
	a1.free();
	q1.free();
	//Recusrive loop
	vec a(A.getHeight());
	a.SetParallel(true);
	vec q(A.getHeight());
	q.SetParallel(true);
	vec qj(A.getHeight());
	qj.SetParallel(true);
	double r;
	for (int i=2; i < A.getHeight()+1; i++){
		q = A.getColumn(i);
		a = A.getColumn(i);
		for (int j=1; j < i;j++){
			qj = Q.getColumn(j);
			r = qj*a;
			R(j,i) = r;
			q = qj*(-r)+q;
		}
		r = q.norm(2);
		R(i,i) = r;
		q = q*(1/r);
		Q.pushColumn(q,i);
	}
	a.free();
	q.free();
	qj.free();
	return std::make_tuple(Q,R);
}


