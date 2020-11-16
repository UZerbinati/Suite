#include "../suite.hpp"
#include "iteractive.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <omp.h>

int ResidualStop(spmat &A,vec b,vec x,double eps){
	vec r(b.getLen());
	r = b-A*x;
	if (r.norm(2) < eps){
		return 1;
	}else{
		return 0;
	}
}
vec Jacobi(spmat &A,vec b,vec guess,int JacobiIT,double eps){
	/*	|JACOBI METHOD|
	 *	x_{k+1} = D^{-1}[b-(L+U)x_{k}]
	 *	where D=diag(A), L is the lower triangular part of A
	 *	and U is the upper triangular of A.
	 */
	vec x0(guess.getLen());
	x0 =  guess;
	assert(A.getWidth() == A.getHeight() && "Matrix must be square, for the Jacobi Method.");
	int k = 0;
	double S = 0;
	vec x(b.getLen());
	while(k < JacobiIT){
		for(int i=1; i < A.getWidth()+1;i++){
			S = 0;
			for(int j=1; j < A.getHeight()+1;j++){
				if (j != i){
					//Element-wise y_k =(L+U)x_k
					S = S + A.getData(i,j)*x0.getData(j-1);
				}
			}
			//Update the solution iteration
			//Element-wise x_{k+1} = D^{-1}(b-y_k);
			x.setData((1/A.getData(i,i))*(b.getData(i-1)-S),i-1);	
		}
		k = k+1;
		x0 = x;
		if( ResidualStop(A,b,x,eps) == 1){ break; }
	}
	return x;
}
vec GauBSiedel(spmat &A,vec b,vec guess,int itmax,double eps){
	/*	|GAUSS-SIEDEL METHOD|
	 *	L^{*}x_{k+1} = Ux_{k}]
	 *	where D=diag(A), L is the lower triangular part of A,
	 *	U is the upper triangular of A, and L^{*} = D+L;
	 */
	assert(A.getWidth() == A.getHeight() && "Matrix must be square, for the Jacobi Method.");
	vec x(guess.getLen());
	int k = 0;
	double S = 0;
	x = guess;
	while(k < itmax){
		for (int i=1;i < A.getWidth()+1; i++){
			S=0;
			for (int j=1; j < A.getHeight()+1; j++){
				if(j!=i){
					//Element-wise yk = U * x_k
					S = S + A.getData(i,j)*x.getData(j-1);
				}
			}
			//Element-wise x_k = L^{-1} y_k
			x.setData((b.getData(i-1)-S)/A.getData(i,i),i-1);
		}
		k++;
		if( ResidualStop(A,b,x,eps) == 1){ break; }
	}
	return x;
}
vec SOR(spmat &A,vec b,vec guess,double omega,int itmax,double eps){
	assert(omega < 2 && "Relaxation parameters must be smaller then 2.");
	assert(1< omega && "Relaxation parameters must be greater then 1.");
	vec x(guess.getLen());
	int k = 0;
	double S = 0;
	x = guess;
	while(k < itmax){
		for (int i=1;i < A.getWidth()+1; i++){
			S=0;
			for (int j=1; j < A.getHeight()+1; j++){
				if(j!=i){
					S = S + A.getData(i,j)*x.getData(j-1);
				}
			}
			//Element-wise convex combination of Gauss-Siedel iteraction
			x.setData((1-omega)*x.getData(i-1)+(b.getData(i-1)-S)*(omega/A.getData(i,i)),i-1);
		}
		k++;
		if( ResidualStop(A,b,x,eps) == 1){ break; }
	}
	return x;
}
