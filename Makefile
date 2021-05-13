CXX=g++ -std=c++14 
all: base python 
base: test.o complex.o vector.o diff.o matrix.o linearsys.o decomposition.o sparse.o iteractive.o 1DGeo.o ODE.o FD.o quadrature.o FV.o 2DGeo.o automata.o root.o
	$(CXX) -o test Build/test.o Build/complex.o Build/vector.o Build/diff.o Build/matrix.o Build/linearsys.o Build/sparse.o Build/iteractive.o Build/1DGeo.o Build/ODE.o Build/FD.o Build/quadrature.o Build/FV.o Build/2DGeo.o Build/automata.o Build/root.o
python: LAParallel.o 
	$(CXX) -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` Py/suite.cpp -fopenmp -o Py/Build/suite`python3-config --extension-suffix`
#expr:
#	bison -d Expr/expr.ypp
#	flex Expr/expr.l
#	$(CXX) -o Expr/expreval Expr/expr.tab.cpp Expr/lex.yy.c
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
decomposition.o: matrix.o
	$(CXX) -c LA/decomposition.cpp -o Build/decomposition.o
LAParallel.o: vector.o matrix.o
	$(CXX) -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` -c Parallel/LA.cpp -fopenmp -o Build/LAParallel.o
sparse.o: vector.o LA/sparse.cpp
	$(CXX) -c LA/sparse.cpp -o Build/sparse.o
iteractive.o: vector.o sparse.o LA/iteractive.cpp
	$(CXX) -c LA/iteractive.cpp -o Build/iteractive.o
1DGeo.o: vector.o FD.o Geo/1D.cpp
	$(CXX) -c Geo/1D.cpp -o Build/1DGeo.o
ODE.o: root.o Calc/ode.cpp
	$(CXX) -c Calc/ode.cpp -o Build/ODE.o
FD.o: 1DGeo.o Calc/fd.cpp
	$(CXX) -c Calc/fd.cpp -o Build/FD.o
quadrature.o: 1DGeo.o Calc/quadrature.cpp
	$(CXX) -c Calc/quadrature.cpp -o Build/quadrature.o
FV.o: 1DGeo.o quadrature.o Calc/fv.cpp
	$(CXX) -c Calc/fv.cpp -o Build/FV.o
2DGeo.o: Geo/2D.cpp
	$(CXX) -c Geo/2D.cpp -o Build/2DGeo.o
automata.o: 1DGeo.o Discrete/automata.cpp
	$(CXX) -c Discrete/automata.cpp -o Build/automata.o
root.o: Calc/root.cpp
	$(CXX) -c Calc/root.cpp -o Build/root.o
