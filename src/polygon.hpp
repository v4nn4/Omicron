#ifndef __POLYGON__
#define __POLYGON__

#include <vector>

struct vector3d;

typedef std::vector<vector3d> vertices;

struct polygon
{
	vertices vertices;
};

class polyhedra_utilities
{
public:
	static polygon generate_discrete_circle(const vector3d& u, const int& n);
	static polygon generate_discrete_sphere(const vector3d& u, const int& n);
	static polygon generate_human_head();
	static bool is_close_xy(const std::vector<vector3d>& u, const vector3d& v, const double& eps);
};

#endif