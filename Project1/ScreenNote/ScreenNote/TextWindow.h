#ifndef _TEXT_WINDOW_H_
#define _TEXT_WINDOW_H_

#include "stdafx.h"
#include "Resource.h"

namespace myTextWindow
{ 
	
	//TCHAR className[] = L"MDI_TEXT_CHILD";
	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
	ATOM MyRegisterClass(HINSTANCE hInstance);
	
}

#endif