#ifndef AUTOMATAHEADREF
#define AUTOMATAHEADREF

#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

class Automata
{
	private:
		Mesh cells;
		int state;
		MeshFunction cells_state;
		std::vector <std::function <MeshFunction(MeshFunction)>> rules;
	public:
		Automata(Mesh mesh, int s);
		void Initialize(MeshFunction I);
		int getNStates();
		MeshFunction getState();
		void addRule(std::function<MeshFunction(MeshFunction)>);
		void Run();
};

#endif
