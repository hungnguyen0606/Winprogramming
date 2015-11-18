#ifndef _WINDOW_MANAGER_H_
#define _WINDOW_MANAGER_H_

#include "stdafx.h"
#include "Resource.h"

namespace myWinManager
{
	HWND addChildWindow(HWND hWndMDIClient, HINSTANCE owner, TCHAR* className, TCHAR* title, DWORD style);

}
#endif