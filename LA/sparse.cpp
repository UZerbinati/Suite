#include "../suite.hpp"
#include "sparse.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <omp.h>

/*TOOLBOX, need to be optimizd !*/

int find(int arr[], int len, int seek)
{
    for (int i = 0; i < len; ++i)
    {
        if (arr[i] == seek) return i;
    }
    return -1;
}
void pairsort(int a[], double b[], int n) 
{ 
    pair<int, double> pairt[n]; 
  
    // Storing the respective array 
    // elements in pairs. 
    for (int i = 0; i < n; i++)  
    { 
        pairt[i].first = a[i]; 
        pairt[i].second = b[i]; 
    } 
  
    // Sorting the pair array. 
    sort(pairt, pairt + n); 
      
    // Modifying original arrays 
    for (int i = 0; i < n; i++)  
    { 
        a[i] = pairt[i].first; 
        b[i] = pairt[i].second; 
    } 
} 

/*
 * We decided to use COO as sparse matrix format, even if has greater computational cost, due to the fact that is easier to implement.

 */

spmat::spmat(int n,int m)
{
	/* 
	 * [1 0 0 
	 *  0 1 0]
	 */
	height = n; width = m;
	
	if (m >= n){
		p = n;
	}else{
		p = m;
	}
	value = new double[p];
	P = new int[p];
	for (int i =0; i < p;i++){
		value[i] = 1.0;
		P[i] = (i*width)+i;
	}
		
}
void spmat::empty()
{
	/* 
	 * [1 0 0 
	 *  0 1 0]
	 */

	for (int i =0; i < p;i++){
		value[i] = 0.0;
		P[i] = (i*width)+i;
	}
		
}
spmat::spmat(){

}
spmat::~spmat(){

}
double& spmat::operator() (int i, int j)
{
	int k;
	k = (width*(i-1))+j-1;
	int m = find(P,p,k);
	return value[m];
}
int spmat::getWidth(){
	return width;
}
int spmat::getHeight(){
	return height;
}
double& spmat::getData (int i, int j)
{
	int k;
	k = (width*(i-1))+j-1;
	int m = find(P,p,k);
	return value[m];
}
double& spmat::getItem(int *idx,int size){
	assert(size == 2 && "Error: too many indicies.");
	assert(0< idx[0] && "Error: indicies out of range.");
	assert(0< idx[1] && "Error: indicies out of range.");
	assert(idx[0] < height+1&& "Error: indicies out of range.");
	assert(idx[1] < width+1 && "Error: indicies out of range.");
	int k;
	k = (width*(idx[0]-1))+idx[1]-1;
	//std::cout << "k:" << k << std::endl;
	int m = find(P,p,k);
	return value[m];
}

void spmat::setItem(int *idx,int size, double data){
	assert(size == 2 && "Error: too many indicies.");
	assert(0< idx[0] && "Error: indicies out of range.");
	assert(0< idx[1] && "Error: indicies out of range.");
	assert(idx[0] < height+1&& "Error: indicies out of range.");
	assert(idx[1] < width+1 && "Error: indicies out of range.");
	int k;
	int *new_P;
	double *new_value;
	k = (width*(idx[0]-1))+idx[1]-1;
	int m = find(P,p,k);
	//std::cout << "m: " << m << ", p:" << p<<std::endl;
	if (m == -1){
		new_P = new int[p+1];
		new_value = new double[p+1];
		for (int l=0;l < p;l++){
			new_P[l] = P[l];
			//std::cout << "P[" << l << "]: " << P[l] << std::endl;
			//std::cout << "new_P[" << l << "]: " << new_P[l] << std::endl;
			new_value[l] =  value[l];
			//std::cout << "value[" << l << "]: " << value[l] << std::endl;
			//std::cout << "new_value[" << l << "]: " << new_value[l] << std::endl;
		}
		new_P[p] = k;
		new_value[p] = data;
		//std::cout << "new_P[" << p << "]: " << new_P[p] << std::endl;
		//std::cout << "new_value[" << p << "]: " << new_value[p] << std::endl;
		p=p+1;

		delete []P;
		delete []value;

		P = new_P;
		value = new_value;

		//std::cout << "P[" << p-1 << "]: " << P[p-1] << std::endl;
		//std::cout << "value[" << p-1 << "]: " << value[p-1] << std::endl;

		pairsort(P,value,p);
	}else{
		value[m] = data;
	}
}
vec operator*(const spmat &M, const vec &v){
	vec result(M.height);
	int j = 0;
	int i = 0;
	for (int k=0; k < M.p; k++){
		i = (M.P[k]%M.width+1);
		j = (M.P[k]/M.height+1);
		int m = find(M.P,M.p,M.P[k]);
		result[i] = result[i] + M.value[m]*v.getData(j-1);
	}	
	return result;
}
int spmat::getSize(){
	return p;
}
spmat operator+(spmat A,spmat B){
	assert(A.height == B.height && "Matrix don't have same dimensions");
	assert(A.width == B.width && "Matrix don't have same dimensions");
	spmat M(A.height,A.width);
	int Aj;
	int Ai;
	int Bj;
	int Bi;
	double elval= 0.0;
	std::vector <int> idx;
	M.empty();
	for (int k=0;k<A.p;k++){
		Aj = (A.P[k]%A.width+1);
		Ai = (A.P[k]/A.height+1);
		idx = {Ai,Aj};
		elval = M.getItem(idx.data(),idx.size())+A.getItem(idx.data(),idx.size());
		std::cout << "A(" << Ai << "," << Aj << ")->" << A(Ai,Aj)<< std::endl;
		M.setItem(idx.data(),idx.size(),elval);	
	}
	for (int k=0;k<B.p;k++){
		Bj = (B.P[k]%B.width+1);
		Bi = (B.P[k]/B.height+1);
		idx = {Bi,Bj};
		elval = M.getItem(idx.data(),idx.size())+B.getItem(idx.data(),idx.size());
		M.setItem(idx.data(),idx.size(),elval);	
	}
	return M;
}
spmat operator*(const double lambda, spmat A){
	spmat M(A.getHeight(),A.getWidth());
	int Ai;
	int Aj;
	std::vector <int> idx;
	double elval;
	M.empty();
	for (int k=0; k < A.p; k++){
		Aj = (A.P[k]%A.width+1);
		Ai = (A.P[k]/A.height+1);
		idx = {Ai,Aj};
		elval = lambda*A.getItem(idx.data(),idx.size());
		M.setItem(idx.data(),idx.size(),elval);	
	}
	return M;
}
std::string spmat::toString(){	
	std::string out;
	for(int k=0; k < p;k++){
		out = out+"["+std::to_string(P[k])+",("+std::to_string(P[k]/width+1)+","+std::to_string(int(P[k]%width)+1)+")]->"+std::to_string(value[k])+"\n";
	}
	return out;
}
