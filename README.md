# Suite
[![Documentation Status](https://readthedocs.org/projects/suite/badge/?version=latest)](https://suite.readthedocs.io/en/latest/?badge=latest)
## Build
To build this project we first have to build first the dependencies.
We begin building PyBind11:
```console
cd Dependencies
cd pybind11
mkdir build
cd build
cmake ..
make
```
We now can build the Suite:
```console
make
```
## Description of Prj structure
- Build, contains the pre-linked compiled classes used in the project.
- Calc, contains classes related to calculus.
- LA, contains classes related to linear algebra and numerical linear algebra.
- Dependencies, contains pybind11 (as git module)
- Py, cotains the suite.cpp file that is the PyBind11 binder and the build folder contains the wrap of the suite library for Python.
- test.cpp and suite.hpp are file used to keep track of all the things implemented in library and check if they work correctly.
