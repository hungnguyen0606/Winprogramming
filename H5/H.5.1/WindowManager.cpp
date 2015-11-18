#include "stdafx.h"
#include "WindowManager.h"

HWND myWinManager::addChildWindow(HWND hWndMDIClient, HINSTANCE owner, TCHAR* className, TCHAR* title, DWORD style)
{
	
	MDICREATESTRUCT mdiCreate;
	mdiCreate.szClass = (LPCWSTR) className;
	mdiCreate.szTitle = (LPCWSTR) title;
	mdiCreate.style = style;
	mdiCreate.hOwner = owner;
	mdiCreate.x = CW_USEDEFAULT;
	mdiCreate.y = CW_USEDEFAULT;
	mdiCreate.cx = CW_USEDEFAULT;
	mdiCreate.cy = CW_USEDEFAULT;
	//mdiCreate.
	mdiCreate.style = 0;
	// Tham số “mở”, chuyển đến WM_CREATE
	mdiCreate.lParam = NULL;
	
	return (HWND)SendMessage(hWndMDIClient, WM_MDICREATE, 0, (LONG)
		(LPMDICREATESTRUCT)&mdiCreate);
}