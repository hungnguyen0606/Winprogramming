#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "stdafx.h"
#include "Resource.h"

class ghInst
{
private:
	static HINSTANCE hinst;
public:
	HINSTANCE& operator()()
	{
		return hinst;
	}
};

class hWndFrame
{
private:
	
public:
	static HWND hwndframe;
	HWND& operator()()
	{
		return hwndframe;
	}
};

class hWndMDIClient
{
private:
	
public:
	static HWND hwndMDIClient;
	HWND& operator()()
	{
		return hwndMDIClient;
	}
};
#endif