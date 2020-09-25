#include "matrix.hpp"
#include <iostream>

mat::mat(int n,int m)
{
	height = n; width = m;
	data = new double[n*m];	
	for(int i=0; i < n*m;i++){
		data[i]=0;
	}
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
		out=out+std::to_string(data[width*i+height-1])+"]\n";
	}
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
mat& mat::operator=(const mat &A){
	for(int i=0; i < height*width; i++){
		data[i] = A.data[i];
	}
	return *this;
}
void mat::free(){
	delete[] data;
}
