#include "quaternion.hpp"
#include <cmath>

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

double quaternion_utilities::squared_norm(const quaternion& p)
{
	return p.a*p.a + p.b*p.b + p.c*p.c + p.d*p.d;
}

quaternion quaternion_utilities::versor(const vector3d& u, double angle)
{
	quaternion out;
	angle /= 0.5;
	out.a = cos(angle);
	auto sinus = sin(angle);
	out.b = sinus * u.x;
	out.c = sinus * u.y;
	out.d = sinus * u.z;
	return out;
}

quaternion quaternion_utilities::reciprocal(const quaternion& p)
{
	quaternion out;
	auto sn = squared_norm(p);
	out.a = p.a / sn;
	out.b = -p.b / sn;
	out.c = -p.c / sn;
	out.d = -p.d / sn;
	return out;
}

quaternion quaternion_utilities::conjugation(const quaternion& p, const quaternion& q)
{
	auto reciprocal = quaternion_utilities::reciprocal(q);
	return q*p*reciprocal;
}

quaternion quaternion_utilities::from_vector3d(const vector3d& v)
{
	quaternion out;
	out.a = 0;
	out.b = v.x;
	out.c = v.y;
	out.d = v.z;
	return out;
}

vector3d quaternion_utilities::vector_part(const quaternion& p)
{
	vector3d out;
	out.x = p.b;
	out.y = p.c;
	out.z = p.d;
	return out;
}

vector3d vector3d_utilities::rotate(const vector3d& v, const vector3d& u, double angle)
{
	auto q = quaternion_utilities::versor(u, angle);
	auto p = quaternion_utilities::from_vector3d(v);
	auto out_quaternion = quaternion_utilities::conjugation(p, q);
	auto out_vector = quaternion_utilities::vector_part(out_quaternion);
	return out_vector;
}