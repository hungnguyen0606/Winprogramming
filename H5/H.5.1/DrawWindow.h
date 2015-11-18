#ifndef _DRAW_WINDOW_H_
#define _DRAW_WINDOW_H_

#include "stdafx.h"
#include "Resource.h"

namespace myDrawWindow
{

	//TCHAR className[] = L"MDI_TEXT_CHILD";
	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
	ATOM MyRegisterClass(HINSTANCE hInstance);

}

#endif