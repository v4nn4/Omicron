#ifndef __SINCOS__
#define __SINCOS__
#include <math.h>

#define M_2_OVER_PI 0.63661977236

inline void sincos(double angle, double* sinus, double* cosinus)
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	_asm
	{
		fld QWORD PTR[angle]
		fsincos
		mov ebx, [cosinus]; get the pointer into ebx
		fstp QWORD PTR[ebx]; store the result through the pointer
		mov ebx, [sinus]
		fstp QWORD PTR[ebx]
	}
#else
	*sinus = sin(angle);
	*cosinus = cos(angle);
#endif
}

#endif