#ifndef VECTORHEADERDEF
#define VECTORHEADERDEF

class vec
{
	private:
		double* data;
		int len;
	public:
		vec(int vlen);
		vec();
		~vec();
		int getLen() const;
		double& operator[] (int i);
		void from_Array(double *array, int size);
		vec& operator= (const vec& othervec);
		vec operator+ (const vec& addendum) const;
		vec operator-(const vec& othervec) const;
		vec operator*(const double lambda) const;
		friend vec operator*(double lambda, vec& a);
		double norm(double p);
		std::string toString();
		void free();
		double getData(int j) const;

};

#endif
