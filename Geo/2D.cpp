#include "2D.hpp"

Point2D::Point2D(){
	x = 0;
	y = 0;
}

double Point2D::GetX(){
	return x;
}
double Point2D::GetY(){
	return y;
}

void Point2D::SetX(double xx){
	x = xx;
}
void Point2D::SetY(double yy){
	y = yy;
}

std::vector<double> Point2D::Get(){
	std::vector<double> P = {x,y};
	return P;
}
void Point2D::Set(std::vector<double> P){
	x = P[0];
	y = P[1];
}
std::string Point2D::toString(){
	std::string out;
	out = "(" + std::to_string(x) + "," + std::to_string(y) + ")\n";
	return out;
}

Triangle::Triangle(){
	Point2D zero;
	zero.Set({0.0,0.0,0.0});
	V = {zero,zero,zero};
}
void Triangle::SetVertex(Point2D Q, int k){
	V[k] = Q;
}
Point2D Triangle::GetVertex(int k){
	return V[k];
}
Point2D Triangle::Circumcenter(){
	
	Point2D N;
	
	Point2D A = V[0];
	Point2D B = V[1];
	Point2D C = V[2];

	double D;
	D = 2.0*(A.GetX()*(B.GetY()-C.GetY())+B.GetX()*(C.GetY()-A.GetY())+C.GetX()*(A.GetY()-B.GetY()));
	
	double AA;
	AA = pow(A.GetX(),2)+pow(A.GetY(),2);
	double BB;
	BB = pow(B.GetX(),2)+pow(B.GetY(),2);
	double CC;
	CC = pow(C.GetX(),2)+pow(C.GetY(),2);

	N.SetX((1.0/D)*(AA*(B.GetY()-C.GetY()) + BB*(C.GetY()-A.GetY()) + CC*(A.GetY()-B.GetY()) ));
	N.SetY((1.0/D)*(AA*(-B.GetX()+C.GetX()) + BB*(-C.GetX()+A.GetX()) + CC*(-A.GetX()+B.GetX()) ));
	
	return N;
}
Point2D Triangle::Centeroid(){
	Point2D C;
	C.SetX((1.0/3.0)*(V[0].GetX()+V[1].GetX()+V[2].GetX()));
	C.SetY((1.0/3.0)*(V[0].GetY()+V[1].GetY()+V[2].GetY()));
	return C;
}
double Triangle::Circumradious(){
	
	Point2D A = V[0];
	Point2D B = V[1];
	Point2D C = V[2];

	double D;
	D = 2.0*(A.GetX()*(B.GetY()-C.GetY())+B.GetX()*(C.GetY()-A.GetY())+C.GetX()*(A.GetY()-B.GetY()));
	
	double AA;
	AA = pow(A.GetX(),2)+pow(A.GetY(),2);
	double BB;
	BB = pow(B.GetX(),2)+pow(B.GetY(),2);
	double CC;
	CC = pow(C.GetX(),2)+pow(C.GetY(),2);

	Point2D BI;
	BI.SetX(B.GetX()-A.GetX());	
	BI.SetY(B.GetY()-A.GetY());	

	Point2D CI;
	CI.SetX(C.GetX()-A.GetX());	
	CI.SetY(C.GetY()-A.GetY());	

	//std::cout << "BI: " << BI.toString() << ", " << "CI: " << CI.toString() << std::endl;

	double DI;
	DI = 2.0*(BI.GetX()*CI.GetY()-BI.GetY()*CI.GetX());

	double BBI;
	BBI = pow(BI.GetX(),2)+pow(BI.GetY(),2);
	double CCI;
	CCI = pow(CI.GetX(),2)+pow(CI.GetY(),2);
	double Ux;
	Ux = (1.0/DI)*(CI.GetY()*BBI-BI.GetY()*CCI);
	double Uy;
	Uy = (1.0/DI)*(BI.GetX()*CCI-CI.GetX()*BBI);
	double R;
	R = pow(pow(Ux,2)+pow(Uy,2),0.5);
	return R;
}
std::string Triangle::toString(){
	std::string out = "V1: ";
	out = out + V[0].toString() + "V2: " + V[1].toString() + "V3: " + V[2].toString() + "\n";
	return out;
}
bool inCircle(Triangle T, Point2D P){
	Point2D CircleCenter;
	CircleCenter = T.Circumcenter();
	double CircleRadious;
	CircleRadious = T.Circumradious();
	double d;
	d = sqrt(pow(P.GetX()-CircleCenter.GetX(),2)+pow(P.GetY()-CircleCenter.GetY(),2));
	if  (d<= CircleRadious){
		return true;
	}else{
		return false;
	}
}

int SearchTriangle(std::vector<Triangle> list, Triangle T){
	bool T1; bool T2; bool T3;
	double delta;
	int k;
	for (k=0; k < list.size(); k++){
				delta = abs(list[k].GetVertex(0).GetX()-T.GetVertex(0).GetX()) +abs(list[k].GetVertex(0).GetY()-T.GetVertex(0).GetY());
				T1 = (delta < 1e-8);
				delta = abs(list[k].GetVertex(1).GetX()-T.GetVertex(1).GetX()) +abs(list[k].GetVertex(1).GetY()-T.GetVertex(1).GetY());
				T2 = (delta < 1e-8);
				delta = abs(list[k].GetVertex(2).GetX()-T.GetVertex(2).GetX()) +abs(list[k].GetVertex(2).GetY()-T.GetVertex(2).GetY());
				T3 = (delta < 1e-8);
				if (T1 and T2 and T3){
					break;
				}
	}
	return k;
}

std::vector<Triangle> Deluny(std::vector<Point2D> Ps){
	std::vector <Triangle> Triangles;


	std::vector <std::vector<Triangle>> NTs;
	std::vector<Triangle> Boundary;
	std::vector <Point2D> TrianglesCenter;
	std::vector <double> TrianglesRadious;

	int edge;
	int t;
	int r;
	int s;
	int nindex;
	double delta;
	Triangle Top;
	Triangle Ttmp;

	Triangle T1;
	T1.SetVertex(Ps[0],0);
	T1.SetVertex(Ps[1],1);
	T1.SetVertex(Ps[3],2);

	Triangle T2;
	T2.SetVertex(Ps[2],0);
	T2.SetVertex(Ps[3],1);
	T2.SetVertex(Ps[1],2);
	
	std::vector<Triangle> Ts;
	Ts = {T2};
	NTs.push_back(Ts);
	Ts = {T1};
	NTs.push_back(Ts);


	Triangles.push_back(T1);
	Triangles.push_back(T2);

	TrianglesCenter.push_back(T1.Circumcenter());
	TrianglesRadious.push_back(T1.Circumradious());
	TrianglesCenter.push_back(T2.Circumcenter());
	TrianglesRadious.push_back(T2.Circumradious());
	
	std::vector <int> BadTriangles;
	
	for (int k=0; k < Ps.size(); k++){
		for (int j=0; j < Triangles.size(); j++){
			if(inCircle(Triangles[j],Ps[k])){
				BadTriangles.push_back(j);

			}
		}	
		t = BadTriangles[0];
		Boundary = {};
		edge = 0;
		r = 0;
		while(true){
			Top = Triangles[t];
			if(inCircle(Top,Ps[k])){
				s = (edge+1)%3;
				if (s==-1){
					s=2;
				}

				std::cout << "bad ... "<< std::endl;
				Ttmp.SetVertex(Triangles[t].GetVertex(s),0);

				s = (edge-1)%3;
				if (s==-1){
					s=2;
				}
				Ttmp.SetVertex(Triangles[t].GetVertex(s),1);
				Ttmp.SetVertex(Top.GetVertex(edge),2);
				Boundary.push_back(Ttmp);
				edge = (edge + 1) % 3;
				delta = abs(Boundary[0].GetVertex(0).GetX()-Boundary[Boundary.size()-1].GetVertex(1).GetX()) + abs(Boundary[0].GetVertex(0).GetY()-Boundary[Boundary.size()-1].GetVertex(1).GetY());
				if (delta<1e-8){
					break;
				}
			}else{
				std::cout << "good ..." << std::endl;
				s = (SearchTriangle(NTs[t],Triangles[t])+1) % 3;
				if (s==-1){
					edge=2;
				}else{
					edge=s;
				}
                		t = SearchTriangle(Triangles,Top);
			}	
		}
	}	

	return Triangles;
}
