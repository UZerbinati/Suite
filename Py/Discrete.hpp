#include "../Discrete/automata.hpp"
#include "../Discrete/automata.cpp"

void DiscreteBind(py::module &module){
	py::class_<Automata>(module,"Automata")
		.def("getNStates", &Automata::getNStates)
		.def("getState", &Automata::getState)
		.def("addRule", &Automata::addRule)
		.def("Run", &Automata::Run)
		.def("Init", &Automata::Initialize)	
		.def(py::init<Mesh,int>());
}
