#include "vector3d.hpp"
#include "quaternion.hpp"
#include <math.h>

void vector3d_utilities::rotate(vector3d& v, const vector3d& u, const double& angle)
{
	auto q = quaternion_utilities::versor(u, angle); // vector should be precomputed
	auto p = quaternion_utilities::from_vector3d(v);
	auto out_quaternion = quaternion_utilities::conjugation(p, q);
	v = quaternion_utilities::vector_part(out_quaternion);
}

void vector3d_utilities::rotate(vector3d& v, const quaternion& versor)
{
	auto p = quaternion_utilities::from_vector3d(v);
	auto out_quaternion = quaternion_utilities::conjugation(p, versor);
	v = quaternion_utilities::vector_part(out_quaternion);
}

void vector3d_utilities::rotate(std::vector<vector3d>& v, const quaternion& versor)
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		rotate(v[i], versor);
	}
}

double vector3d_utilities::snorm(const vector3d& u)
{
	return u.x*u.x + u.y*u.y + u.z*u.z;
}

void vector3d_utilities::normalize(vector3d& u)
{
	auto norm = sqrt(vector3d_utilities::snorm(u));
	u.x /= norm;
	u.y /= norm;
	u.z /= norm;
}