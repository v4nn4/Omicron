#include "render.hpp"
#include "math.hpp"
#include "coordinates.hpp"
#include "polygon.hpp"
#include "vector3d.hpp"

void renderer::set_pixel(const int& x, const int& y, const uint32_t& color)
{
	uint32_t& row = reinterpret_cast<uint32_t&>(static_cast<uint8_t*>(_buffer->memory)[_buffer->pitch*y+4*x]);
	row = color;
};

void renderer::clear_screen()
{
	for (auto y = 0; y < _buffer->height;++y)
	{
		for (auto x = 0; x < _buffer->width;++x)
		{
			set_pixel(x, y, 0);
		}
	}
}

void renderer::render(const polygon& pp, const polygon& fp)
{
	screen_coordinates sc{ _aspect_ratio, static_cast<double>(_buffer->width), static_cast<double>(_buffer->height) };
	int x, y;
	for (auto i = 0; i < pp.vertices.size(); ++i)
	{
		coordinates_utilities::world_to_screen(pp.vertices[i], sc, x, y);
		set_pixel(x + 1, y, 0);
		set_pixel(x, y, 0);
		set_pixel(x - 1, y, 0);
		set_pixel(x + 1, y + 1, 0);
		set_pixel(x, y + 1, 0);
		set_pixel(x - 1, y + 1, 0);
		set_pixel(x + 1, y - 1, 0);
		set_pixel(x, y - 1, 0);
		set_pixel(x - 1, y - 1, 0);
	}
	uint32_t color;
	for (auto i = 0; i < fp.vertices.size(); ++i)
	{
		coordinates_utilities::world_to_screen(fp.vertices[i], sc, x, y);
		auto n = static_cast<uint32_t>(floor(0.5 * ( atan(fp.vertices[i].z * fp.vertices[i].z * fp.vertices[i].z * 100) * M_2_OVER_PI + 1) * 255));
		color = static_cast<uint32_t>(n) << 2 * 4 | 0x000000AA;
		set_pixel(x + 1, y, color);
		set_pixel(x, y, color);
		set_pixel(x - 1, y, color);
		set_pixel(x + 1, y + 1, color);
		set_pixel(x, y + 1, color);
		set_pixel(x - 1, y + 1, color);
		set_pixel(x + 1, y - 1, color);
		set_pixel(x, y - 1, color);
		set_pixel(x - 1, y - 1, color);
	}
};