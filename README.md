# Suite

## Build
To build this project we first have to build first the dependencies.
We begin building PyBind11:
	cd Dependencies
	cd pybind11
	mkdir build
	cd build
	cmake ..
	make
We now can build the Suite:
	make
