#include "../Geo/1D.hpp"
#include "../Geo/1D.cpp"

void GeoBind(py::module &module){
	py::class_<line>(module,"line")
		.def(py::init<double,double>());
	py::class_<Mesh>(module,"Mesh")
		.def(py::init<int>())
		.def("UniformMesh", &Mesh::UniformMesh)
		.def("__repr__", &Mesh::toString);
}
