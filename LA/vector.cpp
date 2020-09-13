#include <cmath>
#include <iostream>
#include <cassert>
#include "vector.hpp"

//Allocates memory for a new vector, and copies entries in the vector.
vec::vec (const vec& othervec)
{
	len = othervec.getLen();
	data = new double [len];
	for (int i=0; i < len; i++){
		data[i] = othervec.data[i];
	}
}
//Allocates memory for a new vector given the length, in particular all create vector zero.
vec::vec (int vlen){
	len = vlen;
	data = new double [len];
	for (int i=0; i < len; i++){
		data[i] = 0.0;
	}
}
int vec::getLen() const
{
	return len;
}
