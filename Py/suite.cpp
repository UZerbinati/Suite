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
    	    .def("__setitem__", [](mat &M, std::vector<int> idx,double value) {
			    M.setItem(idx.data(),idx.size(), value);
		}, py::is_operator());

}
