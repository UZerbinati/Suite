#ifndef FDHEADREF
#define FDHEADREF

#include <iostream>
#include <functional>
#include <vector>
#include <cmath>

class FiniteDifference
{
	private:
		Mesh mesh;
	public:
		FiniteDifference();
		FiniteDifference(Mesh m);
		spmat BoundaryOp(BC bc);
		spmat ReactionOp(BC bc, MeshFunction f);
		spmat LaplaceOp(BC bc);
		spmat TransportOp(BC bc,MeshFunction f);
};
class HOFiniteDifference
{
	private:
		Mesh mesh;
		int order;
	public:
		HOFiniteDifference();
		HOFiniteDifference(Mesh m,int p);
		spmat BoundaryOp(BC bc);
		spmat ReactionOp(BC bc, MeshFunction f);
		spmat LaplaceOp(BC bc);
		spmat TransportOp(BC bc,MeshFunction f);
};

#endif
