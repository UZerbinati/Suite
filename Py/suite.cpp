#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>

#include "../LA/complex.hpp"
#include "../LA/complex.cpp"

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

}
