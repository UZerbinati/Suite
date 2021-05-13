#include "../Calc/ode.hpp"
#include "../Calc/ode.cpp"

#include "../Calc/diff.hpp"
#include "../Calc/diff.cpp"


#include "../Calc/fd.hpp"
#include "../Calc/fd.cpp"

#include "../Calc/fv.hpp"
#include "../Calc/fv.cpp"

#include "../Calc/quadrature.hpp"
#include "../Calc/quadrature.cpp"


#include "../Calc/root.hpp"
#include "../Calc/root.cpp"

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
    py::class_<NonLinearODE<vec>>(module,"NonLinearODEs")
	    .def(py::init <int>())
	    .def("setDomain", &NonLinearODE<vec>::setDomain)
	    .def("setCoeff", &NonLinearODE<vec>::setCoefficients)
	    .def("Euler", &NonLinearODE<vec>::Euler)
	    .def("SympEuler", &NonLinearODE<vec>::SympEuler)
	    .def("RK", &NonLinearODE<vec>::RK)
	    .def("setIC", &NonLinearODE<vec>::setIC)
	    .def("__repr__", &NonLinearODE<vec>::toString);
    //FINITE DIFFERENCE
    py::class_<FiniteDifference>(module,"FiniteDifference")
	    .def(py::init <Mesh>())
	    .def("BoundaryOp", &FiniteDifference::BoundaryOp)
	    .def("TransportOp", &FiniteDifference::TransportOp)
	    .def("ReactionOp", &FiniteDifference::ReactionOp)
	    .def("LaplaceOp", &FiniteDifference::LaplaceOp);
    py::class_<HOFiniteDifference>(module,"HOFiniteDifference")
	    .def(py::init <Mesh,int>())
	    .def("setType", &HOFiniteDifference::setType)
	    .def("LaplaceOp", &HOFiniteDifference::LaplaceOp)
	    .def("BoundaryOp", &HOFiniteDifference::BoundaryOp);
    //FINITE VOLUME
    py::class_<FiniteVolume>(module,"FiniteVolume")
	    .def(py::init <Mesh>());
    //ROOT
    module.def("Newton", [](std::function<double(double)> f, std::function <double(double)> df,double x0,int itmax, double tol, int m) {
	return Newton(f,df,x0,itmax,tol,m);
    },py::arg("f"),py::arg("df"),py::arg("x0"),py::arg("itmax")=25,py::arg("tol")=0.00000001,py::arg("m")=1);
    module.def("AutoNewton", [](std::function<double(double)> f, double h,double x0,int itmax, double tol, int m) {
	return AutoNewton(f,h,x0,itmax,tol,m);
    },py::arg("f"),py::arg("h"),py::arg("x0"),py::arg("itmax")=25,py::arg("tol")=0.00000001,py::arg("m")=1);
    //QUADRATURE
    module.def("NewtonCotes", [](MeshFunction f, double h, int order) {
	return NewtonCotes(f, h, order);
    },py::arg("f"),py::arg("h"),py::arg("order"));
    module.def("Integrate", [](MeshFunction f, Mesh mesh) {
	return Integrate(f, mesh);
    },py::arg("f"),py::arg("mesh"));

}
