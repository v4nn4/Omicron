#include "polyhedra.hpp"
#include "vector3d.hpp"

polyhedra polyhedra_utilities::generate_discrete_circle(const vector3d& /*u*/, const int& n)
{
	// For now u = {0,0,1}
	// nth unit roots : exp(2*i*pi/k)
	std::vector<vector3d> vertices(n);
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		vertices[i].x = cos(2 * M_PI *i / n);
		vertices[i].y = sin(2 * M_PI *i / n);
	}
	auto out = polyhedra{ vertices };
	return out;
}

bool polyhedra_utilities::is_close_xy(const std::vector<vector3d>& u, const vector3d& v, const double& eps)
{
	if (u.size() == 0)
		return false;
	for (size_t i = 0; i < u.size(); ++i)
	{
		vector3d w = u[i];
		w.z = 0.0;
		if (vector3d_utilities::snorm(w - v) < eps*eps)
			return true;
	}
	return false;
}