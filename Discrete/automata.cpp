#include "../suite.hpp"
#include "automata.hpp"

Automata::Automata(Mesh mesh, int s){
	cells = mesh;
	state = s;
}
void Automata::Initialize(MeshFunction I){
	cells_state = I;
}
int Automata::getNStates(){
	return state;
}
MeshFunction Automata::getState(){
	return cells_state;
}
void Automata::addRule(std::function <MeshFunction(MeshFunction)> rule){
	rules.push_back(rule);
}
void Automata::Run(){
	for (int k=0; k < rules.size(); k++){
		//std::cout << "Running rule ..." << std::endl;
		//std::cout << rules[k](cells_state).toString() << std::endl;
		cells_state = rules[k](cells_state);
	}
}
