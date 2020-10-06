CXX=g++
all: test python
test: test.o complex.o vector.o diff.o matrix.o linearsys.o
	$(CXX) -o test Build/test.o Build/complex.o Build/vector.o Build/diff.o Build/matrix.o Build/linearsys.o
python: TestParallel.o 
	$(CXX) -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` Py/suite.cpp -fopenmp -o Py/Build/suite`python3-config --extension-suffix`
test.o: test.cpp
	$(CXX) -c test.cpp -o Build/test.o
diff.o: Calc/diff.cpp
	$(CXX) -c Calc/diff.cpp -o Build/diff.o
complex.o: LA/complex.cpp
	$(CXX) -c LA/complex.cpp -o Build/complex.o
vector.o: LA/vector.cpp
	$(CXX) -c LA/vector.cpp -o Build/vector.o
matrix.o: LA/matrix.cpp
	$(CXX) -c LA/matrix.cpp -o Build/matrix.o
linearsys.o: vector.o matrix.o LA/linearsys.cpp
	$(CXX) -c LA/linearsys.cpp -o Build/linearsys.o
TestParallel.o: vector.o matrix.o
	$(CXX) -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` -c Parallel/Test.cpp -fopenmp -o Build/TestParallel.o
