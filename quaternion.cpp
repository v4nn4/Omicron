#include "quaternion.hpp"
#include "vector3d.hpp"
#include "math.hpp"

double quaternion_utilities::snorm(const quaternion& p)
{
	return p.a*p.a + p.b*p.b + p.c*p.c + p.d*p.d;
}

quaternion quaternion_utilities::versor(const vector3d& u, const double& angle)
{
	quaternion out;
	auto midangle = angle * 0.5;
	double sinus;
	sincos(midangle, &sinus, &out.a);
	out.b = sinus * u.x;
	out.c = sinus * u.y;
	out.d = sinus * u.z;
	return out;
}

quaternion quaternion_utilities::reciprocal(const quaternion& p)
{
	quaternion out;
	auto one_over_sn = 1/snorm(p);
	out.a = p.a * one_over_sn;
	out.b = -p.b * one_over_sn;
	out.c = -p.c * one_over_sn;
	out.d = -p.d * one_over_sn;
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
	out.a = 0.;
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