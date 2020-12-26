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
};

#endif
