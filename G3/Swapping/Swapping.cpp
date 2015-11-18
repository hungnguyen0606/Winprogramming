// Swapping.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

HINSTANCE hInst;

__declspec(dllexport) void Swap(int &a, int &b)
{
	int c;
	c = a;
	a = b;
	b = c;
}