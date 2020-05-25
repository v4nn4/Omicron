#ifndef __VECTOR3D__
#define __VECTOR3D__

#include <math.h>
#include <vector>

struct quaternion;

struct vector3d
{
	double x;
	double y;
	double z;
};

class vector3d_utilities
{
public:
	static void rotate(vector3d& x, const vector3d& u, const double& angle);
	static void rotate(vector3d& v, const quaternion& versor);
	static void rotate(std::vector<vector3d>& v, const quaternion& versor);
	static double snorm(const vector3d& u);
	static void normalize(vector3d& u);
};

#include "quaternion.hpp"
inline quaternion operator*(const quaternion& p, const quaternion& q)
{
	quaternion out;
	out.a = p.a * q.a - p.b * q.b - p.c * q.c - p.d * q.d;
	out.b = p.a * q.b + p.b * q.a + p.c * q.d - p.d * q.c;
	out.c = p.a * q.c - p.b * q.d + p.c * q.a + p.d * q.b;
	out.d = p.a * q.d + p.b * q.c - p.c * q.b + p.d * q.a;
	return out;
}

inline quaternion operator+(const quaternion& p, const quaternion& q)
{
	quaternion out;
	out.a = p.a + q.a;
	out.b = p.b + q.b;
	out.c = p.c + q.c;
	out.d = p.d + q.d;
	return out;
}

inline vector3d operator-(const vector3d &u, const vector3d& v)
{
	vector3d out;
	out.x = u.x - v.x;
	out.y = u.y - v.y;
	out.z = u.z - v.z;
	return out;
}

#endif