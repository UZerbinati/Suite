#include "../suite.hpp"
#include <omp.h>
#include <cmath>
#include <tuple>


mat ParallelChol(mat &A){
	assert(A.getHeight() == A.getWidth() && "Error: Matrix must be square to perform cholesky");
	assert(A(1,1) > 0 && "Error: Matrix must be positive definite");

	//Init L matrix that we are going to fill.
	mat L(A.getHeight(),A.getHeight());
	double S; double R;
	int k; int n;
	for (int j=1; j < A.getHeight()+1; j++){
		S = 0.0;
		for (k=1;k < j; k++){
			S = S + L(j,k)*L(j,k); //We compute the sum \sum_{k=1}^{j-1} L_{j,k}^2}

		}
		L(j,j) = sqrt(A(j,j)-S); //We compute the diagonal element using L_{j,j} = \sqrt{A_{j,j} - \sum_{k=1}^{j-1} L_{j,k}^2}
		#pragma omp parallel for private(n,k,R) shared (A,L,j) schedule (static)
		for (n=j+1; n < A.getHeight()+1; n++){
			R = 0.0;
			for (int k=1;k < j; k++){
				R = R + L(n,k)*L(j,k); //We compute \sum_{k=1}^{j-1} L_{n,k}L_{j,k}
			}
			L(n,j) = (A(n,j)-R)/L(j,j); //We compute the non diagonal element using L_{j,j}L_{n,j} = A_{n,j} -\sum_{k=1}^{j-1} L_{n,k}L_{j,k} for n > j
		}
	}
	return L;
}

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


