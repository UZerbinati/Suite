#include "../suite.hpp"
#include "matrix.hpp"
#include <iostream>
#include <omp.h>

mat::mat(int n,int m)
{
	height = n; width = m;
	parallel = false;
	data = new double[n*m];	
	for(int i=0; i < n*m;i++){
		data[i]=0;
	}
}
mat::mat(){
}
mat::~mat()
{
	
}
int mat::getHeight(){
	return height;
}
int mat::getWidth(){
	return width;
}
double& mat::operator() (unsigned i, unsigned j)
{
	/*[ 0 0 0 0
	 *  0 0 0 0 
	 *  0 0 0 0 ]
	*/
	int k;
	k = (width*(i-1))+j-1;
	return data[k];
}
double& mat::getItem(int *idx,int size){
	assert(size == 2 && "Error: too many indicies.");
	int k;
	k = (width*(idx[0]-1))+idx[1]-1;
	return data[k];	
}
void mat::setItem(int *idx,int size, double value){
	int k;
	k = (width*(idx[0]-1))+idx[1]-1;
	data[k] = value;
}
std::string mat::toString(){

	std::string out;
	for (int i=0; i < height;i++){
		out = out+"[";
		for(int j=0; j <width-1;j++){
			out = out+std::to_string(data[width*i+j])+",";
		}
		out=out+std::to_string(data[width*i+width-1])+"]\n";
	}

	/*for (int k=0; k < height*width;k++){
		std::cout << "(" << k << ")->" << data[k] << std::endl;
	}*/

	return out;

}
void mat::from_Array(double *array, int size){
	std::cout << size << std::endl;
	for (int i=0; i < height; i++){
		for(int j=0;j < width;j++){
			data[width*i+j] = array[width*i+j];	
		}
	}
}
mat mat::operator+(const mat &A) const
{
	assert(height == A.height && "Error: matricies must have the same height.");
	assert(width == A.width && "Error: matricies must have the same width.");
	mat result(height,width);
	for(int i=0; i < height*width; i++){
		result.data[i] = data[i]+A.data[i];
	}
	/*for(int j=0; j< height*width; j++){
		std::cout << result.data[j] << " ";
	}
	std::cout << std::endl;*/
	return result;	
}
mat mat::operator-(const mat &A) const
{
	assert(height == A.height && "Error: matricies must have the same height.");
	assert(width == A.width && "Error: matricies must have the same width.");
	mat result(height,width);
	for(int i=0; i < height*width; i++){
		result.data[i] = data[i]-A.data[i];
	}
	return result;	
}
mat mat::operator*(const double lam) const{
	mat result(height,width);
	for(int i=0; i < height*width; i++){
		result.data[i] = lam*data[i];
	}
	return result;
}
vec operator*(const mat &M,const vec &v){
	vec result(M.height);
	if (M.parallel == false){
		for (int k=0; k < M.width; k++){
			for (int j=0; j < M.height; j++){
				result[k+1] = result.getData(k) + M.data[M.width*k+j]*v.getData(j);
			}
		}
	}else{
		
		#pragma omp parallel
		{
		    double w_prv[M.height];
		    int i,j;
		    for (i = 0; i < M.width; i++) {
			#pragma omp for
			for (j = 0; j < M.height; j++) {
			    w_prv[j] =w_prv[j]+ M.data[M.width*i+j]*v.getData(j);
			}
		    }
		    #pragma omp critical
		    {
			for(i=0; i<M.height; i++){
				result[i+1] += w_prv[i];
			}    
		}
		}	
	}
	return result;
}
mat& mat::operator=(const mat &A){
	for(int i=0; i < height*width; i++){
		data[i] = A.data[i];
	}
	return *this;
}
mat mat::operator*(const mat &A) const{
	/*
	 * [a b c  [1 2 3
	 *  d e f   4 5 6
	 *  g h i]  7 8 9]
	 */
	assert(width == A.height && "Error: dimension missmatch.");
	mat B(height,A.width);
	double S;
	for (int i=1; i<height+1; i++){
		for (int j=1; j < A.width+1;j++){
			S = 0.0; 
			for (int k=1; k<width+1;k++){
				S += data[width*(i-1)+k-1]*A.data[A.width*(k-1)+j-1];
			}		
			B(i,j) = S;
		}	
	}
	return B;
}
void mat::free(){
	delete[] data;
}
void mat::SetParallel(bool set){
	parallel = set;
}
bool mat::GetParallel(){
	return parallel;
}
void mat::pushColumn(vec &a,int i){
	for (int k=0;k < height;k++){
		data[width*k+i-1] = a[k+1];
	}	
}
vec mat::getColumn(int i){
	vec result(height);
	for (int k=0; k < height;k++){
		result[k+1] = data[width*k+i-1];
	}
	return result;
}
mat mat::transpose(){
	mat A(width,height);
	for (int k=0; k < height;k++){
		for (int n=0; n < width; n++){
			A(n+1,k+1) = data[width*k+n];
		}	
	}
	return A;
}
mat Vander(vec v,int m){
	int N;
	N = v.getLen();
	mat M(N,m);
	for (int k=1; k < N+1;k++){
		M(k,1) = 1.0;
		for (int l=2; l < m+1;l++){
			M(k,l) = pow(v.getData(k-1),(l-1));
		}
	}
	return M;
}
