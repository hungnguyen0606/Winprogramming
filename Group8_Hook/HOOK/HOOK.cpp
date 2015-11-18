// HOOK.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "HOOK.h"

HINSTANCE hinstlib;
// This is an example of an exported variable
HOOK_API int nHOOK=0;
HHOOK hHook = 0;

// This is an example of an exported function.
HOOK_API int fnHOOK(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see HOOK.h for the class definition
CHOOK::CHOOK()
{
	return;
}
LRESULT CALLBACK calc(
	_In_ int    nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	)
{
	if (nCode < 0)
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	KBDLLHOOKSTRUCT* ps = (KBDLLHOOKSTRUCT*)lParam;
	if (wParam == WM_KEYDOWN)
	if (ps->vkCode == VK_F6)
	{
		WinExec("calc.exe", SW_SHOW);
	}

	return CallNextHookEx(hHook, nCode, wParam, lParam);
}
HOOK_API void setHook()
{
	if (hHook != NULL)
		return;
	SetWindowsHookEx(WH_KEYBOARD_LL, calc, hinstlib, 0);
}

HOOK_API void unHook()
{
	if (hHook == NULL)
		return;
	UnhookWindowsHookEx(hHook);
}