#include "../Calc/ode.hpp"
#include "../Calc/ode.cpp"

#include "../Calc/diff.hpp"
#include "../Calc/diff.cpp"

void CalcBind(py::module &module){
    //DIFFERENTIATION
    py::class_<Diff>(module,"Diff")
	    .def(py::init <>())
	    .def("push",&Diff::push)
    	    .def("call", &Diff::call)
    	    .def("set_h", &Diff::set_h)
	    .def("set_type", &Diff::set_type);
    py::class_<LinearODE>(module,"LinearODE")
	    .def(py::init <int>())
	    .def("setDomain", &LinearODE::setDomain)
	    .def("setCoeff", &LinearODE::setCoefficient)
	    .def("setIC", &LinearODE::setIC)
	    .def("ScalarEuler", &LinearODE::ScalarEuler)
	    .def("__repr__", &LinearODE::toString);
}
