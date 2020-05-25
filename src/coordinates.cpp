#include "coordinates.hpp"
#include "vector3d.hpp"

void coordinates_utilities::world_to_screen(const vector3d& v, const screen_coordinates& sc, int& x, int& y)
{
	x = sc.width*(v.x + sc.aspect_ratio) / (2 * sc.aspect_ratio);
	y = sc.height*(v.y + sc.aspect_ratio) / (2 * sc.aspect_ratio);
}