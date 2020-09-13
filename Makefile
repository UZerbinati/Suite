CXX=g++
all: test
test: test.o complex.o vector.o diff.o
	$(CXX) -o test Build/test.o Build/complex.o Build/vector.o Build/diff.o
test.o:
	$(CXX) -c test.cpp -o Build/test.o
diff.o: Calc/diff.cpp
	$(CXX) -c Calc/diff.cpp -o Build/diff.o
complex.o: LA/complex.cpp
	$(CXX) -c LA/complex.cpp -o Build/complex.o
vector.o: LA/vector.cpp
	$(CXX) -c LA/vector.cpp -o Build/vector.o

