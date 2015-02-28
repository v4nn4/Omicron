#pragma once
#include <vector>

struct vector3d;

typedef std::vector<vector3d> vertices;

struct polyhedra
{
	vertices vertices;
};

class polyhedra_utilities
{
public:
	static polyhedra generate_discrete_circle(const vector3d& u, const int& n);
	static bool is_close_xy(const std::vector<vector3d>& u, const vector3d& v, const double& eps);
};