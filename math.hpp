#pragma once

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