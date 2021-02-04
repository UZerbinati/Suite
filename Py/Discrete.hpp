#include "../Discrete/automata.hpp"
#include "../Discrete/automata.cpp"

void DiscreteBind(py::module &module){
	py::class_<Automata>(module,"Automata")
		.def(py::init<Mesh>());
}
