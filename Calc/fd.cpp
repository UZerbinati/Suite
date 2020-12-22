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
	M(1,1) = 1;
	for (int k=2;k < len;k++){
		K = {k,k-1};
		M.setItem(K.data(),K.size(),1.0/pow(mesh.getSize(k),2));
		M(k,k) = -2/pow(mesh.getSize(k),2);
		K = {k,k+1};
		M.setItem(K.data(),K.size(),1.0/pow(mesh.getSize(k),2));
	}
	M(len,len) = 1;
	return M;
}
