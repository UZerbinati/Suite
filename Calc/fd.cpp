#include "../suite.hpp"
#include "fd.hpp"

FiniteDifference::FiniteDifference(){
}
FiniteDifference::FiniteDifference(Mesh m){
	mesh = m;
}
spmat FiniteDifference::LaplaceOp(BC bc){
	int len = bc.get_function()->export_vec().getLen();
	spmat M(len,len);
	std::vector <int> K;
	if (bc.get_Type() == "DIRICHLET"){	
		if (bc.getDim()[0] == 1 and bc.getDim()[1]==1){
			M(1,1) = 0;
			for (int k=2;k < len;k++){
				K = {k,k-1};
				M.setItem(K.data(),K.size(),1.0/(mesh.getSize(k-1)*mesh.getSize(k)));
				M(k,k) = -2/(mesh.getSize(k-1)*mesh.getSize(k));
				K = {k,k+1};
				M.setItem(K.data(),K.size(),1.0/(mesh.getSize(k-1)*mesh.getSize(k)));
			}
			M(len,len) = 0;
			return M;
		}
	}
}
spmat FiniteDifference::ReactionOp(BC bc, MeshFunction f){
	int len = bc.get_function()->export_vec().getLen();
	spmat M(len,len);
	std::vector <int> K;
	if (bc.get_Type() == "DIRICHLET"){	
		if (bc.getDim()[0] == 1 and bc.getDim()[1]==1){
			M(1,1) = 0;
			for (int k=2;k < len;k++){
				std::vector <double> P = { mesh.getLineElement(k-1).getPoint(0)+0.5*mesh.getSize(k-1) };
				M(k,k) = f.eval(P,1)[0];
			}
			M(len,len) = 0;
			return M;
		}
	}
}
spmat FiniteDifference::BoundaryOp(BC bc){
	int len = bc.get_function()->export_vec().getLen();
	spmat M(len,len);
	std::vector <int> K;
	if (bc.get_Type() == "DIRICHLET"){	
		if (bc.getDim()[0] == 1 and bc.getDim()[1]==1){
			M(1,1) = 1;
			for (int k=2;k<len;k++){
				M(k,k) = 0;
			}
			M(len,len) = 1;
			return M;
		}
	}
}
spmat FiniteDifference::TransportOp(BC bc,MeshFunction f){
	int len = bc.get_function()->export_vec().getLen();
	spmat M(len,len);
	M.empty();
	std::vector <int> K;
	if (bc.get_Type() == "DIRICHLET"){	
		if (bc.getDim()[0] == 1 and bc.getDim()[1]==1){
			M(1,1) = 0;
			for (int k=2;k < len;k++){
				std::vector <double> P = { mesh.getLineElement(k-1).getPoint(0)+0.5*mesh.getSize(k-1) };
				K = {k,k-1};
				M.setItem(K.data(),K.size(),-(f.eval(P,1)[0]*1.0)/(2*mesh.getSize(k-1)));
				K = {k,k+1};
				M.setItem(K.data(),K.size(),(f.eval(P,1)[0]*1.0)/(2*mesh.getSize(k)));
			}
			M(len,len) = 0;
			return M;
		}
	}
}
