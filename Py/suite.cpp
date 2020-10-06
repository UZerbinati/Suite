#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>

#include "../LA/complex.hpp"
#include "../LA/complex.cpp"

#include "../Calc/diff.hpp"
#include "../Calc/diff.cpp"

#include "../LA/vector.hpp"
#include "../LA/vector.cpp"

#include "../LA/matrix.hpp"
#include "../LA/matrix.cpp"

#include "../LA/linearsys.hpp"
#include "../LA/linearsys.cpp"

#include "../Parallel/Test.cpp"

class Test
{
	private:
		double x;
		double y;
	public:
		Test(double a,double b);
};

Test::Test(double a,double b){
	x=a;
	y=b;
}

namespace py = pybind11;

PYBIND11_MODULE(suite, module) {
    module.attr("release") = "0.0.1";
    module.def("ParallelTest", []() {
      /* Release GIL before calling into C++ code */
      py::gil_scoped_release release;
      ParallelTest();
    });
    module.def("parallel_calc_pi", [](int n) {
      /* Release GIL before calling into C++ code */
      py::gil_scoped_release release;
      return parallel_calc_pi(n);
    });
    module.def("calc_pi", [](int n) {
      return calc_pi(n);
    });
    py::class_<Test>(module, "Test")
	    .def(py::init <double, double>());
    //COMPLEX NUMBERS
    py::class_<Complex>(module, "Complex")
	    .def(py::init <double, double>())
	    .def(py::self + py::self)
	    .def(py::self - py::self)
	    .def(py::self == py::self)
	    .def("__repr__", &Complex::toString)
	    .def("polar", &Complex::polar)
	    .def("abs", &Complex::abs)
	    .def("arg", &Complex::arg)
	    .def("Real", &Complex::Real)
	    .def("Imag", &Complex::Imag)
	    .def("pow", &Complex::pow);
    //DIFFERENTIATION
    py::class_<Diff>(module,"Diff")
	    .def(py::init <>())
	    .def("push",&Diff::push)
    	    .def("call", &Diff::call)
    	    .def("set_h", &Diff::set_h)
	    .def("set_type", &Diff::set_type);
    //VECTOR
    py::class_<vec>(module, "vec")
	    .def(py::init <int>())
	    .def(py::self + py::self)
	    .def(py::self - py::self)
	    .def(py::self*double())
	    .def(double()*py::self)
	    .def("__eq__", [](vec& a, vec&b){
			    a = b;
	    },py::is_operator())
	    .def("norm", &vec::norm)
	    .def("len", &vec::getLen)
    	    .def("__getitem__", [](vec &a, int i) {
			    double value;
			    value = a[i];
			    return value;
		}, py::is_operator())
    	    .def("__setitem__", [](vec &a, int i,double value) {
			    a[i] = value;
		}, py::is_operator())
	    .def("from_Array", [](vec &a,std::vector<double> array) {
			    a.from_Array(array.data(), array.size());
		})
	    .def("free", &vec::free)
	    .def("__repr__", &vec::toString);
    //MATRIX
    py::class_<mat>(module, "mat")
	    .def(py::init <int, int>())
	    .def("__eq__", [](mat& a, mat&b){
			    a = b;
	    },py::is_operator())
	    .def(py::self + py::self)
	    .def(py::self - py::self)
	    .def(py::self * double())
	    .def("free", &mat::free)
    	    .def("__getitem__", [](mat &M, std::vector<int> index) {
			    double value;
			    value = M.getItem(index.data(),index.size());
			    return value;
		}, py::is_operator())
	    .def("__repr__", &mat::toString)
	    .def("toString", &mat::toString)
    	    .def("from_Array", [](mat &M, std::vector<double> array) {
			    M.from_Array(array.data(), array.size());
		}, py::is_operator())
    	    .def("__mul__", [](mat &M, vec &v) {
			    return M*v;
		}, py::is_operator())
    	    .def("__setitem__", [](mat &M, std::vector<int> idx,double value) {
			    M.setItem(idx.data(),idx.size(), value);
		}, py::is_operator())
	    .def_property("parallel", &mat::GetParallel, &mat::SetParallel);
    //LINSYS
    py::class_<LinSys>(module, "LinSys")
	    .def(py::init <mat&, vec&>())
	    .def("BackSub", &LinSys::BackSub)
	    .def("Gauss", &LinSys::Gauss)
	    .def("setType", &LinSys::setType)
	    .def("getMatrix", &LinSys::getMatrix)
	    .def("__repr__", &LinSys::toString);
	
}
