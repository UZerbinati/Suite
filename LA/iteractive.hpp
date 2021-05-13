vec Jacobi(spmat &A,vec b,vec x0,int itmax,double eps);
vec GauBSeidel(spmat &A,vec b,vec x0,int itmax,double eps);
vec SOR(spmat &A,vec b,vec guess,double omega,int itmax,double eps);
vec ConjugateGradient(spmat &A,vec b,vec x0,int itmax, double eps);
