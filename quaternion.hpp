#ifndef __QUATERNION__
#define __QUATERNION__

struct vector3d;

struct quaternion
{
	double a;
	double b;
	double c;
	double d;
};

class quaternion_utilities
{
public:
	static quaternion versor(const vector3d& u, const double& angle);
	static quaternion conjugation(const quaternion& p, const quaternion& q);
	static quaternion from_vector3d(const vector3d& x);
	static vector3d vector_part(const quaternion& p);
private:
	static double snorm(const quaternion& p);
	static quaternion reciprocal(const quaternion& p);
};

#endif