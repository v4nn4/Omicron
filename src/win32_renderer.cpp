#include "render.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
void win32_renderer::initialize()
{

};
#else
void win32_renderer::initialize()
{

};
#endif