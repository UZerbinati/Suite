#ifndef VECTORHEADERDEF
#define VECTORheADERDEF

class vec
{
	private:
		double* data;
		int len;
	public:
		vec(const vec& othervec);
		vec(int vlen);
		~vec();
		int getLen() const;
};

#endif
