#ifndef TWODGEOHEADREF
#define TWODGEOHEADREF

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

class Point2D {
	private:
		double x;
		double y;
	public:
		Point2D();
		double GetX();
		double GetY();
		std::vector<double> Get();
		void SetX(double xx);
		void SetY(double yy);
		void Set(std::vector<double> P);
		std::string toString();

};
class Triangle {
	private:
		std::vector<Point2D> V;
	public:
		Triangle();
		void SetVertex(Point2D Q, int k);
		Point2D GetVertex(int k);
		Point2D Circumcenter();
		double Circumradious();
		Point2D Centeroid();
		std::string toString();
};

bool inCircle(Triangle T, Point2D P);

int SearchTriangle(std::vector<Triangle> list, Triangle T);


std::vector<Triangle> Deluny(std::vector<Point2D> Ps);

#endif
