#ifndef __RENDER__
#define __RENDER__

#include <stdint.h>

struct polygon;

struct buffer
{
	void *memory;
	int width;
	int height;
	int bytes_per_pixel;
	int pitch;
};

class renderer
{
public:
    virtual void initialize() = 0;
    void render(const polygon& pp, const polygon& fp);
    void set_pixel(const int& x, const int& y, const uint32_t& color);
	void clear_screen();
protected:
    buffer* _buffer;
    double _aspect_ratio;
};

class macos_renderer : public renderer
{
public:
    void initialize();
};

class win32_renderer : public renderer
{
public:
	void initialize();
};

#endif