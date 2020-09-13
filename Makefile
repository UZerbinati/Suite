CXX=g++
all: test
python: 
	$(CXX) -O3 -Wall -std=c++11 -fPIC "python3 -m pybind11 --includes" example.cpp -o example"python3-config --extension-suffix"
test: test.o complex.o vector.o diff.o
	$(CXX) -o test test.o complex.o vector.o diff.o
diff.o: Calc/diff.cpp
	$(CXX) -c Calc/diff.cpp
complex.o: LA/complex.cpp
	$(CXX) -c LA/complex.cpp
vector.o: LA/vector.cpp
	$(CXX) -c LA/vector.cpp

