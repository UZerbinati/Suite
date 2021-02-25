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
		}else if(bc.getDim()[0] == 2 and bc.getDim()[1]==1){
			if (mesh.getType()=="SQUARE-UNIFORM"){
				M.empty();
				double h;
				double x;
				double y;
				std::vector <double> P;
				int L;

				L = sqrt(len);
				h = mesh.getSize(0);

				for (int k=0;k < len;k++){
					x = mesh.getContainer()[0]+h*(k%L);
					y = mesh.getContainer()[2]+h*(floor(k/L));
					P = {x,y};
					std::cout << "(" << k%L << "," << floor(k/L) << ")->("<<x<<","<<y<<")" << std::endl;
					if (bc.getGeo().eval(P)<-(1.0+(1/mesh.getElementNumber()))/L){
						K = {k+1,k};
						M.setItem(K.data(),K.size(),1.0/(h*h));
						M(k+1,k+1) = -4.0/(h*h);
						K = {k+1,k+2};
						M.setItem(K.data(),K.size(),1.0/(h*h));
						if (k+1+L < len){
							K = {k+1,k+1+L};
							M.setItem(K.data(),K.size(),1.0/(h*h));
						}
						if (k+1-L > 1){
							K = {k+1,k+1-L};
							M.setItem(K.data(),K.size(),1.0/(h*h));
						}
					}else if (bc.getGeo().eval(P)>(1.0+(1/mesh.getElementNumber()))/L){
					}else{
						M(k+1,k+1) = 0.0;
					}
				}

				return M;
			}
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
	M.empty();
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
	if (mesh.getType() == "SQUARE-UNIFORM"){
		if(bc.getDim()[0] == 2 and bc.getDim()[1]==1){
			double h;
			double x;
			double y;
			std::vector <double> P;
			int L;

			L = sqrt(len);
			h = mesh.getSize(0);

			for (int k=0;k < len;k++){
				x = mesh.getContainer()[0]+h*(k%L);
				y = mesh.getContainer()[2]+h*(floor(k/L));
				P = {x,y};
				if (bc.getGeo().eval(P)<-(1.0+(1/mesh.getElementNumber()))/L){
				}else if (bc.getGeo().eval(P)>(1.0+(1/mesh.getElementNumber()))/L){
				}else{
					bc.setBI(k);
					M(k+1,k+1) = 1.0;
				}
			}

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
HOFiniteDifference::HOFiniteDifference(){
}
HOFiniteDifference::HOFiniteDifference(Mesh m, int p){
	mesh = m;
	type = "CENTER";
	order = p;
}
void HOFiniteDifference::setType(std::string t){
	type = t;
}
spmat HOFiniteDifference::LaplaceOp(BC bc){
	int len = bc.get_function()->export_vec().getLen();
	spmat M(len,len);
	M.empty();
	std::vector <int> K;
	int k;
	if (bc.get_Type() == "DIRICHLET"){	
		if (bc.getDim()[0] == 1 and bc.getDim()[1]==1){
			M(1,1) = 0;
			if (order==3){
				if (type=="RIGHT"){
					std::cout << "Right FD method of order 3" << std::endl;
					for (int k=2; k <= len-order;k++){
						K = {k,k-1};
						M.setItem(K.data(),K.size(),11.0/(12.0*mesh.getSize(k-1)*mesh.getSize(k)));
						M(k,k) = -20.0/(12*mesh.getSize(k-1)*mesh.getSize(k));
						K = {k,k+1};
						M.setItem(K.data(),K.size(),6.0/(12.0*mesh.getSize(k-1)*mesh.getSize(k)));
						K = {k,k+2};
						M.setItem(K.data(),K.size(),4.0/(12.0*mesh.getSize(k-1)*mesh.getSize(k)));
						K = {k,k+3};
						M.setItem(K.data(),K.size(),-1.0/(12.0*mesh.getSize(k-1)*mesh.getSize(k)));
					}
				}
				
			}
			if (order==4){
				if (type=="CENTER"){
					for (k=order-1;k < len-1;k++){
							K = {k,k-2};
							M.setItem(K.data(),K.size(),-1.0/(12.0*mesh.getSize(k-1)*mesh.getSize(k)));
							K = {k,k-1};
							M.setItem(K.data(),K.size(),16.0/(12.0*mesh.getSize(k-1)*mesh.getSize(k)));
							M(k,k) = -30.0/(12*mesh.getSize(k-1)*mesh.getSize(k));
							K = {k,k+1};
							M.setItem(K.data(),K.size(),16.0/(12.0*mesh.getSize(k-1)*mesh.getSize(k)));
							K = {k,k+2};
							M.setItem(K.data(),K.size(),-1.0/(12.0*mesh.getSize(k-1)*mesh.getSize(k)));
					}
				}
				if (type=="RIGHT"){
					std::cout << "Right FD method of order 4" << std::endl;
					for (int k=2; k <= len-order;k++){
						K = {k,k-1};
						M.setItem(K.data(),K.size(),10.0/(12.0*mesh.getSize(k-1)*mesh.getSize(k)));
						M(k,k) = -15.0/(12*mesh.getSize(k-1)*mesh.getSize(k));
						K = {k,k+1};
						M.setItem(K.data(),K.size(),-4.0/(12.0*mesh.getSize(k-1)*mesh.getSize(k)));
						K = {k,k+2};
						M.setItem(K.data(),K.size(),14.0/(12.0*mesh.getSize(k-1)*mesh.getSize(k)));
						K = {k,k+3};
						M.setItem(K.data(),K.size(),-6.0/(12.0*mesh.getSize(k-1)*mesh.getSize(k)));
						K = {k,k+4};
						M.setItem(K.data(),K.size(),+1.0/(12.0*mesh.getSize(k-1)*mesh.getSize(k)));
					}
				}
			}
			M(len,len) = 0;
			return M;
		}
	}
}
int HOFiniteDifference::getOrder(){
	return order;
}
std::string HOFiniteDifference::getType(){
	return type;
}
spmat HOFiniteDifference::BoundaryOp(BC bc){
	int len = bc.get_function()->export_vec().getLen();
	spmat M(len,len);
	M.empty();
	std::vector <int> K;
	if (bc.get_Type() == "DIRICHLET"){	
		if (bc.getDim()[0] == 1 and bc.getDim()[1]==1){
			if (order==3){
				if (type == "RIGHT"){
					M(1,1) = 1;
					for (int k=len; k>len-order;k--){
						M(k,k)=1;
					}
				}
			}
			if(order==4){
				if (type=="CENTER"){
					M(1,1) = 1;
					M(2,2) = 1;
					M(len-1,len-1) = 1;
					M(len,len) = 1;
				}
				if (type == "RIGHT"){
					M(1,1) = 1;
					for (int k=len; k>len-order;k--){
						M(k,k)=1;
					}
				}
			}
			return M;
		}
	}
}
