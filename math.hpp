#pragma 
#define M_2_OVER_PI 0.63661977236
#define M_PI 3.14159265358979323846

inline void sincos(double angle, double* sinus, double* cosinus)
{
	_asm
	{
		fld QWORD PTR[angle]
		fsincos
		mov ebx, [cosinus]; get the pointer into ebx
		fstp QWORD PTR[ebx]; store the result through the pointer
		mov ebx, [sinus]
		fstp QWORD PTR[ebx]
	}
}