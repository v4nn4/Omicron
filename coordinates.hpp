#pragma once

struct vector3d;

struct screen_coordinates
{
	double aspect_ratio;
	double width;
	double height;
};

class coordinates_utilities
{
public:
	static void world_to_screen(const vector3d& v, const screen_coordinates& screen_coordinates, int& x, int& y);
};