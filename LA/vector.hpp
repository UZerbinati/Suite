#ifndef VECTORHEADERDEF
#define VECTORHEADERDEF

#include <vector>

class vec
{
	private:
		double* data;
		int len;
		bool Parallel;
	public:
		vec(int vlen);
		vec();
		~vec();
		int getLen() const;
		double& operator[] (int i);
		void from_Array(double *array, int size);
		std::vector<double> to_Array();
		vec& operator= (const vec& othervec);
		vec operator+ (const vec& addendum) const;
		vec operator-(const vec& othervec) const;
		vec operator*(const double lambda) const;
		double operator*(const vec& u) const;
		friend vec operator*(double lambda, vec& a);
		double norm(double p);
		std::string toString();
		void free();
		double getData(int j) const;
		void setData(double value, int j) const;
		void SetParallel(bool set);
		bool GetParallel();

};

#endif
