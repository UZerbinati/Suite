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
