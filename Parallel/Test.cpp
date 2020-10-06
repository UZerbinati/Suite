#include "Test.hpp"
#include <omp.h>
#include <pybind11/pybind11.h>
#include <iostream>

namespace py = pybind11;

void ParallelTest(){
	py::gil_scoped_acquire acquire;
	#pragma omp parallel
   	{
        	std::cout << "This is a multicare parallel test for the suite library." << std::endl;
    	}
}

double parallel_calc_pi(int n) {
  /* Acquire GIL before calling Python code */
  py::gil_scoped_acquire acquire;

  int i;
  double step = 1.0/n;
  double s = 0;

  #pragma omp parallel
  {
    double x;
    #pragma omp for reduction(+:s)
    for (i=0; i<n; i++) {
      x = (i+0.5) * step;
      s += 4.0/(1 + x*x);
    }
  }
  return step * s;
};

double calc_pi(int n) {

  int i;
  double step = 1.0/n;
  double s = 0;

  {
    double x;
    for (i=0; i<n; i++) {
      x = (i+0.5) * step;
      s += 4.0/(1 + x*x);
    }
  }
  return step * s;
};
