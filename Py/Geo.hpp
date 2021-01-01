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
		.def("getType", &Mesh::getType)
		.def("getLineElement", &Mesh::getLineElement)
		.def("getElNumber", &Mesh::getElementNumber)
		.def("__repr__", &Mesh::toString);
	//MESH FUNCTION
	py::class_<MeshFunction>(module,"MeshFunction")
		.def(py::init <Mesh,int>())
		.def("vec_export", &MeshFunction::export_vec)
		.def("vec_import", &MeshFunction::import_vec)
		.def("pushFunction", &MeshFunction::pushFunction)
		.def("getDim", &MeshFunction::getDim)

		.def("eval", &MeshFunction::eval);
	//BOUNDARY CONDITIONS
	py::class_<BC>(module,"BoundaryCondition")
		.def(py::init <std::string,MeshFunction>())
		.def("apply", &BC::apply);
}
