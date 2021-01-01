#include "../Calc/ode.hpp"
#include "../Calc/ode.cpp"

#include "../Calc/diff.hpp"
#include "../Calc/diff.cpp"


#include "../Calc/fd.hpp"
#include "../Calc/fd.cpp"

#include "../Calc/quadrature.hpp"
#include "../Calc/quadrature.cpp"

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
    py::class_<LinearODE<vec>>(module,"LinearODEs")
	    .def(py::init <int>())
	    .def("setDomain", &LinearODE<vec>::setDomain)
	    .def("setCoeff", &LinearODE<vec>::setCoefficient)
	    .def("setIC", &LinearODE<vec>::setIC)
	    .def("setSolver", &LinearODE<vec>::setSolver)
	    .def("Euler", &LinearODE<vec>::ScalarEuler)
	    .def("__repr__", &LinearODE<vec>::toString);
    //NON LINEAR ODE
    py::class_<NonLinearODE<double>>(module,"NonLinearODE")
	    .def(py::init <int>())
	    .def("setDomain", &NonLinearODE<double>::setDomain)
	    .def("setCoeff", &NonLinearODE<double>::setCoefficients)
	    .def("setIC", &NonLinearODE<double>::setIC)
	    .def("Euler", &NonLinearODE<double>::Euler)
	    .def("__repr__", &NonLinearODE<double>::toString);
    //FINITE DIFFERENCE
    py::class_<FiniteDifference>(module,"FiniteDifference")
	    .def(py::init <Mesh>())
	    .def("BoundaryOp", &FiniteDifference::BoundaryOp)
	    .def("TransportOp", &FiniteDifference::TransportOp)
	    .def("ReactionOp", &FiniteDifference::ReactionOp)
	    .def("LaplaceOp", &FiniteDifference::LaplaceOp);
    //QUADRATURE
    module.def("NewtonCotes", [](MeshFunction f, double h, int order) {
	return NewtonCotes(f, h, order);
    },py::arg("f"),py::arg("h"),py::arg("order"));
    module.def("Integrate", [](MeshFunction f, Mesh mesh) {
	return Integrate(f, mesh);
    },py::arg("f"),py::arg("mesh"));

}
