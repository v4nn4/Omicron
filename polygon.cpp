#include "polygon.hpp"
#include "vector3d.hpp"
#include "math.hpp"

polygon polyhedra_utilities::generate_discrete_circle(const vector3d& /*u*/, const int& n)
{
	std::vector<vector3d> vertices(n);
	double sintheta, costheta;
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		sincos(2 * M_PI*i / n, &sintheta, &costheta);
		vertices[i].x = costheta;
		vertices[i].y = sintheta;
	}
	auto out = polygon{ vertices };
	return out;
}

polygon polyhedra_utilities::generate_discrete_sphere(const vector3d& /*u*/, const int& n)
{
	std::vector<vector3d> vertices(n*n);
	double sinphi, cosphi, sintheta, costheta;
	for (size_t i = 0; i < n; ++i)
	{
		sincos(M_PI*i / n, &sinphi, &cosphi);
		double sinphi = sin(M_PI *i / n);
		for (size_t j = 0; j < n; ++j)
		{
			sincos(2*M_PI*j / n, &sintheta, &costheta);
			vertices[i*n + j].x = costheta*sinphi;
			vertices[i*n + j].y = sintheta*sinphi;
			vertices[i*n + j].z = cosphi;
		}
	}
	auto out = polygon{ vertices };
	return out;
}

bool polyhedra_utilities::is_close_xy(const std::vector<vector3d>& u, const vector3d& v, const double& eps)
{
	double limit = eps*eps;
	if (u.size() == 0)
		return false;
	for (size_t i = 0; i < u.size(); ++i)
	{
		auto w = u[i];
		w.z = 0.0;
		if (vector3d_utilities::snorm(w - v) < limit)
			return true;
	}
	return false;
}