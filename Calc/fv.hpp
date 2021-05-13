#ifndef FVHEADREF
#define FVHEADREF
class FiniteVolume{
	private:
		Mesh mesh;
	public:
		FiniteVolume(Mesh m);
		template <class GeoEl> vec IntegralApp(MeshFunction u);
	

};
#endif
