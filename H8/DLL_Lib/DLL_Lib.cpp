// DLL_Lib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DLL_Lib.h"

#define EXPORT __dclspec(dllexport)
#define IMPORT __dclspec(dllimport)
// This is an example of an exported variable
DLL_LIB_API int nDLL_Lib=0;

// This is an example of an exported function.
DLL_LIB_API int fnDLL_Lib(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see DLL_Lib.h for the class definition
CDLL_Lib::CDLL_Lib()
{
	return;
}


DLL_LIB_API int Cong(int a, int b)
{
	return a + b;
}
DLL_LIB_API int Tru(int a, int b)
{
	return a - b;
}
DLL_LIB_API int Nhan(int a, int b)
{
	return a*b;
}
DLL_LIB_API int Chia(int a, int b)
{
	return a / b;
}