#include "../Geo/1D.hpp"
#include "../Geo/1D.cpp"

void GeoBind(py::module &module){
	//LINE
	py::class_<line>(module,"line")
		.def(py::init<double,double>())
		.def("getPoint", &line::getPoint);
	//MESH
	py::class_<Mesh>(module,"Mesh")
		.def(py::init<int>())
		.def("UniformMesh", &Mesh::UniformMesh)
		.def("getDim", &Mesh::getDimension)
		.def("getSize", &Mesh::getSize)
		.def("getElement", &Mesh::getElement)
		.def("getElNumber", &Mesh::getElementNumber)
		.def("__repr__", &Mesh::toString);
	//MESH FUNCTION
	py::class_<MeshFunction>(module,"MeshFunction")
		.def(py::init <Mesh,int>())
		.def("pushFunction", &MeshFunction::pushFunction)
		.def("eval", &MeshFunction::eval);
}
