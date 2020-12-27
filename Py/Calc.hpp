#include "../Calc/ode.hpp"
#include "../Calc/ode.cpp"

#include "../Calc/diff.hpp"
#include "../Calc/diff.cpp"


#include "../Calc/fd.hpp"
#include "../Calc/fd.cpp"

void CalcBind(py::module &module){
    //DIFFERENTIATION
    py::class_<Diff>(module,"Diff")
	    .def(py::init <>())
	    .def("push",&Diff::push)
    	    .def("call", &Diff::call)
    	    .def("set_h", &Diff::set_h)
	    .def("set_type", &Diff::set_type);
    //LINEAR ODE
    py::class_<LinearODE<double>>(module,"LinearODE")
	    .def(py::init <int>())
	    .def("setDomain", &LinearODE<double>::setDomain)
	    .def("setCoeff", &LinearODE<double>::setCoefficient)
	    .def("setIC", &LinearODE<double>::setIC)
	    .def("Euler", &LinearODE<double>::ScalarEuler)
	    .def("__repr__", &LinearODE<double>::toString);
    //FINITE DIFFERENCE
    py::class_<FiniteDifference>(module,"FiniteDifference")
	    .def(py::init <Mesh>())
	    .def("BoundaryOp", &FiniteDifference::BoundaryOp)
	    .def("TransportOp", &FiniteDifference::TransportOp)
	    .def("ReactionOp", &FiniteDifference::ReactionOp)
	    .def("LaplaceOp", &FiniteDifference::LaplaceOp);
}
