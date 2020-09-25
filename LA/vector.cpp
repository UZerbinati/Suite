#include <cmath>
#include <iostream>
#include <cassert>
#include <string>
#include "vector.hpp"

//Allocates memory for a new vector given the length, in particular all create vector zero.
vec::vec (int vlen){
	len = vlen;
	data = new double [len];
	for (int i=0; i < len; i++){
		data[i] = 0.0;
	}
}
//Override the destructur operator to free memory
vec::~vec()
{	
	//Dummy due to problm with PyBind11
}
//Method to get the size of a vector
int vec::getLen() const
{
	return len;
}
//Overide the bracket operator
double& vec::operator[] (int i)
{
	assert(i != 0 && "Error: indexing start from one.");
	assert(i < len+1 && "Error: index out of range.");
	int j;
	if (i < 0){
		j = len+i;
	}else{
		j = i-1;
	}
	return data[j];
}
//Construct vector from array and return vector as array
void vec::from_Array(double *array,int size)
{
	assert(len == size && "Error array must have the same size as vector");
	for (int i=0; i < len;i++){
		data[i] = array[i];
	}
}
//Overide the assignment operator
vec& vec::operator=(const vec& othervec)
{
	assert(len == othervec.len && "Error: vector dimension missmatch.");
	for (int i = 0; i < len; i++){
		data[i] = othervec.data[i];
	}
	return *this;
	
}
// Overide sum operator
vec vec::operator+(const vec& addendum) const 
{
	vec result(len);
	assert(len == addendum.len && "Error: vector dimension missmatch.");
	for (int i = 0; i < len; i++)
	{
		result.data[i] = data[i]+addendum.data[i];
	}
	return result;
}
//Overide minus operator
vec vec::operator-(const vec& othervec) const
{
	vec result(len);
	assert(len==othervec.len && "Error: vector dimension missmatch.");
	for (int i=0; i < len;i++){
		result.data[i] = data[i] - othervec.data[i];
	}
	return result;
}
//Override multiplication operator for scalar multiplication
vec vec::operator* (const double lambda) const	
{
	vec result(len);
	for (int i=0; i < len;i++){
		result.data[i] = lambda*data[i];
	}
	return result;
	
}
// Vector to string
std::string vec::toString()
{
	std::string out;
	out = "(";
	for (int i=0; i < len-1;i++){
		out = out+std::to_string(data[i])+",";
	}
	out = out+std::to_string(data[len-1])+")";
	return out;
}
//Function that computes the p-norm (in a very un-efficient way)
double vec::norm(double p)
{
	if (p > 0){
		double S;

		S = 0;
		for(int i=0;i < len;i++){
			S = S+pow(abs(data[i]),p);
		}
		return pow(S,1/p);
	}
	if(p == 0){
		double max;
		max =  data[0];
		for (int i=0; i < len;i++){
			if (data[i] > max){
				max = data[i];
			}
		}
		return max;
	}
}


//overide mutplication on the left, using friend
vec operator*(double lambda,const vec& a)
{
	return a*lambda;
}
void vec::free(){
	std::cout << "Freeing memory" << std::endl;
	delete[] data;
}
