#include "../Geo/1D.hpp"
#include "../Geo/1D.cpp"
#include "../Geo/2D.hpp"
#include "../Geo/2D.cpp"

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

		.def("eval", &MeshFunction::eval)
		.def("norm", &MeshFunction::norm);
	//BOUNDARY CONDITIONS
	py::class_<BC>(module,"BoundaryCondition")
		.def(py::init <std::string,MeshFunction>())
		.def("apply", &BC::apply)
		.def("HOApply", &BC::HOApply);
	//POINT2D
	py::class_<Point2D>(module,"Point2D")
		.def(py::init <>())
		.def("Get", &Point2D::Get)
		.def("GetX", &Point2D::GetX)
		.def("GetY", &Point2D::GetY)
		.def("Set", &Point2D::Set)
		.def("SetX", &Point2D::SetX)
		.def("SetY", &Point2D::SetY)
		.def("__repr__", &Point2D::toString);
	//TRIANGLE
	py::class_<Triangle>(module,"Triangle")
		.def(py::init <>())
		.def("Centeroid", &Triangle::Centeroid)
		.def("__repr__", &Triangle::toString)
		.def("Circumcenter", &Triangle::Circumcenter)
		.def("Circumradious", &Triangle::Circumcenter)
		.def("SetVertex", &Triangle::SetVertex)
		.def("GetVertex", &Triangle::GetVertex);
    	module.def("Deluny", [](std::vector<Point2D> Ps) {
		return Deluny(Ps);
    	});
    	module.def("SearchTriangle", [](std::vector<Triangle> Ts, Triangle T) {
		return SearchTriangle(Ts,T);
    	});
}
