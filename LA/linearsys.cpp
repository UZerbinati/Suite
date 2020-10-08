#include "../suite.hpp"
#include "linearsys.hpp"

LinSys::LinSys(mat &M, vec &v){
	type = "GENERIC";
	ml = 0;
	mr = 0;
	assert(M.getWidth() == v.getLen() && "Error: dimension missmatch");
	A = new mat(M.getHeight(),M.getWidth());
	A = &M;
	b = new vec(v.getLen());
	b = &v;
}
void LinSys::setType(std::string value){
	if(value=="UPPER"){
		type="BAND";
		ml = 0;
		mr = A->getHeight()-1;

	}else if(value=="LOWER"){
		type="BAND";
		ml = A->getHeight()-1;
		mr = 0;
		
	}else{
		type=value;
	}
}
std::string LinSys::toString(){
	std::string out = "";
	out = out + A->toString();
	out = out+"\n";
	out = out+b->toString();
	return out;
}
vec LinSys::BackSub(){
	/*This function solve a linear ssystem using backword substituion, therefore A needs to be upper triangular.
	 *
	 *
	 * Example of the alg
	 * -------------------
	 * Ax = b
	 * [ 1 2 3  [a    [1
	 *   0 1 3   b  =  2
	 *   0 0 1]  c]    3]
	 *
	 *   c = 3/1;
	 *   b = (2-3*c)/1;
	 *   a = (1-2*b+3*c)/1;
	 */ 
	int n;
	int m;
	double tmp;
	double S;
	mat M = *A; //We do this to make bracket usable.
	vec v = *b;

	n = M.getWidth();
	m = M.getHeight();	
	vec x(n);

	if (type == "BAND"){
		if(ml==0 && mr== n-1 && n==m){
			x[n] = v[n]/M(n,n);
			for(int i=n-1; 0 < i; i--){
				S = v[i];
				for(int j=m; 0 < j;j--){
					S = S-M(i,j)*x[j];
				}
				x[i] = S/M(i,i);
			}
		}
		return x;
	} else if (type == "PIVOT-BAND"){
		if(ml==0 && mr== n-1 && n==m){
			x[n] = v[n]/M(n,n);
			for(int i=n-1; 0 < i; i--){
				S = v[i];
				for(int j=m; 0 < j;j--){
					S = S-M(i,j)*x[j];
				}
				x[i] = S/M(i,i);
			}
			for(int k=0; k< m-1; k++){
				tmp = x[k+1];
				x[k+1] = x[P[k]];
				x[P[k]] = tmp;
			}
		}
	}else{
		std::cout << "Error: Matrix must be upper triangular for backword sub" << std::endl;
	}

}
vec LinSys::ForwardSub(){
	/*This function solve a linear ssstem using forward substituion, therefore A needs to be lawer triangular. 
	 *
	 * Example of the alg
	 * -------------------
	 * Ax = b
	 * [ 4 0 0  [a    [1
	 *   2 1 0   b  =  2
	 *   3 2 1]  c]    3]
	 *
	 *   a = 1/4;
	 *   b = (2-2*a)/1;
	 *   a = (1-2*b+3*c)/1;
	 */ 
	int n;
	int m;
	double tmp;
	double S;
	mat M = *A; //We do this to make bracket usable.
	vec v = *b;

	n = M.getWidth();
	m = M.getHeight();	
	vec x(n);

	if (type == "BAND"){
		std::cout << ml << "," << mr << std::endl;
		if(ml==n-1 && mr== 0 && n==m){
			x[1] = v[1]/M(1,1);
			for(int i=2; i< n+1; i++){
				S = v[i];
				for(int j=1; j<i;j++){
					S = S-M(i,j)*x[j];
				}
				x[i] = S/M(i,i);
			}
		}
		return x;
	}else{
		std::cout << "Error: Matrix must be lower triangular for forward sub" << std::endl;
	}

}
mat LinSys::getMatrix(){
	mat M = *A;
	return M;
}
void LinSys::Gauss(int pivoting){
	/*
	 * PIVOTING OPTION
	 * 0) No Pivoting
	 * 1) Non Zero Column Pivoting 
	 * 2) Absolute Value Column Pivoting
	 * 3) Complete Pivoting
	 */
	int n; int m;
	int pivot;
	int cpivot; int rpivot;
	int pivotIndex;
	double tmp;
	double q;
	mat M = *A;
	vec v = *b;
	std::cout << "Gaussian Elimiantion" << std::endl;
	std::cout << M.toString() << std::endl;
	n = M.getWidth();
	m = M.getHeight();	
	if (pivoting == 0){
		for (int k=1; k < n; k++){
			for(int i=k+1;i < n+1; i++){
				q = M(i,k)/M(k,k);
				std::cout << "i: "<< i << ",k: " << k << std::endl; 
				v[i] = v[i] - q*v[k];
				for (int j=k; j < m+1; j++){
					M(i,j) = M(i,j) - q*M(k,j);
				}
			}
		}	
		type = "BAND";
		ml = 0;
		mr = n-1;
	}
	if (pivoting == 1){
		for (int k=1; k < m; k++){
			std::cout << "k: " << k<< std::endl;
			//Pivot Search
			for (int r=k-1; r < m; r++){
				if(M(r+1,k) != 0){
					pivot = r+1;
					break;
				}
				pivot = -1;
			}
			std::cout << "Pivot: " << pivot << std::endl;
			//Assert that a pivot is found
			assert(pivot != -1 && "Error: Matrix is singular.");
			//Swap rows in the known term
			tmp = v[k];
			v[k] = v[pivot];
			v[pivot] = tmp;
			//Swap rows in the matrix
			for (int i=0; i < n; i++){
				tmp = M(k,i+1);
				M(k,i+1) = M(pivot,i+1);
				M(pivot,i+1) = tmp;
			}
			//Subtract rows, multiplied by correct coefficient.
			for (int j=k; j < n; j++){
				q = M(j+1,k)/M(k,k);
				std::cout << "q: " << q << std::endl;
				v[j+1] = v[j+1] - q*v[k];
				for(int i=0; i < m;i++){
					M(j+1,i+1) = M(j+1,i+1) - q*M(k,i+1);
				}	
			}
		std::cout << M.toString() << std::endl;
		}
		type = "BAND";
		ml = 0;
		mr = n-1;
	}
	if (pivoting == 2){
		for (int k=1; k < m; k++){
			std::cout << "k: " << k<< std::endl;
			//Pivot Search
			pivot = k;
			for (int r=k-1; r < m; r++){
				if(M(pivot,k) < M(r+1,k)){
					pivot = r+1;
				}
			}
			std::cout << "Pivot: " << pivot << std::endl;
			//Assert that a pivot is found
			assert(pivot != -1 && "Error: Matrix is singular.");
			//Swap rows in the known term
			tmp = v[k];
			v[k] = v[pivot];
			v[pivot] = tmp;
			//Swap rows in the matrix
			for (int i=0; i < n; i++){
				tmp = M(k,i+1);
				M(k,i+1) = M(pivot,i+1);
				M(pivot,i+1) = tmp;
			}
			//Subtract rows, multiplied by correct coefficient.
			for (int j=k; j < n; j++){
				q = M(j+1,k)/M(k,k);
				std::cout << "q: " << q << std::endl;
				v[j+1] = v[j+1] - q*v[k];
				for(int i=0; i < m;i++){
					M(j+1,i+1) = M(j+1,i+1) - q*M(k,i+1);
				}	
			}
		std::cout << M.toString() << std::endl;
		}
		type = "BAND";
		ml = 0;
		mr = n-1;
	}
	if (pivoting == 3){
		pivotIndex = 0;
		P = new int[m-1];
		for (int k=1; k < m; k++){
			std::cout << "k: " << k<< std::endl;
			//Pivot Search
			cpivot = k;
			rpivot = k;
			for (int r=k-1; r < m; r++){
				for(int s=k-1; s<m; s++){
					if(M(cpivot,rpivot) < M(r+1,s+1)){
						cpivot = r+1;
						rpivot = s+1;
					}
				}
			}
			std::cout << "Pivot: (" << cpivot<<","<<rpivot<<")" << std::endl;
			//Assert that a pivot is found
			assert(pivot != -1 && "Error: Matrix is singular.");
			//Swap rows in the known term
			tmp = v[k];
			v[k] = v[cpivot];
			v[cpivot] = tmp;
			//Swap rows in the matrix
			for (int i=0; i < n; i++){
				tmp = M(k,i+1);
				M(k,i+1) = M(cpivot,i+1);
				M(cpivot,i+1) = tmp;
			}
			//Swap columns in the matrix
			for (int i=0; i < n; i++){
				tmp = M(i+1,k);
				M(i+1,k) = M(i+1,rpivot);
				M(i+1,rpivot) = tmp;
			}	
			P[pivotIndex] = rpivot;
			pivotIndex++;
			//Subtract rows, multiplied by correct coefficient.
			for (int j=k; j < n; j++){
				q = M(j+1,k)/M(k,k);
				std::cout << "q: " << q << std::endl;
				v[j+1] = v[j+1] - q*v[k];
				for(int i=0; i < m;i++){
					M(j+1,i+1) = M(j+1,i+1) - q*M(k,i+1);
				}	
			}
		std::cout << M.toString() << std::endl;
		}
		type = "PIVOT-BAND";
		ml = 0;
		mr = n-1;
	}
}
