#pragma once

struct quaternion
{
	double a;
	double b;
	double c;
	double d;
};

struct vector3d
{
	double x;
	double y;
	double z;
};

class quaternion_utilities
{
public:
	static quaternion versor(const vector3d& u, double angle);
	static quaternion conjugation(const quaternion& p, const quaternion& q);
	static quaternion from_vector3d(const vector3d& x);
	static vector3d vector_part(const quaternion& p);
private:
	static double squared_norm(const quaternion& p);
	static quaternion reciprocal(const quaternion& p);

};

class vector3d_utilities
{
public:
	static vector3d rotate(const vector3d& x, const vector3d& u, double angle);
};