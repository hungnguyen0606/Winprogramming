// LOCK_KEYBOARD.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "LOCK_KEYBOARD.h"

HINSTANCE hinstlib;
HHOOK hHook, mouseHook;
bool isLock = false;
bool oldstate = false;
int flag = 0;
const int lockmask = 7;
const int unlockmask = 11;

// This is an example of an exported variable
LOCK_KEYBOARD_API int nLOCK_KEYBOARD=0;

// This is an example of an exported function.
LOCK_KEYBOARD_API int fnLOCK_KEYBOARD(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see LOCK_KEYBOARD.h for the class definition
CLOCK_KEYBOARD::CLOCK_KEYBOARD()
{
	return;
}

bool isSame(int state, int mask)
{
	if ((state & mask) == mask && (state & (~mask)) == 0)
		return true;
	return false;
}


LRESULT CALLBACK myHookMouse(
	_In_ int    nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	)
{
	if (nCode < 0)
		return CallNextHookEx(mouseHook, nCode, wParam, lParam);
	switch (wParam)
	{
	case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK: case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK: case WM_MOUSEMOVE: case WM_MOUSEWHEEL:
	{
		if (isLock)
			return 1;
		break;
	}
		
	default:
		return CallNextHookEx(mouseHook, nCode, wParam, lParam);
	}
	return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}
LRESULT CALLBACK myHook(
	_In_ int    nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
	)
{
	
	KBDLLHOOKSTRUCT *pkh = (KBDLLHOOKSTRUCT *)lParam;
	INPUT t;

	int bit = -1;
	switch (pkh->vkCode)
	{
	case VK_LSHIFT:case VK_RSHIFT:
	{
		bit = 0;
		break;
	}
	case VK_RCONTROL: case VK_LCONTROL:
	{
		bit = 1;
		break;
	}
	case 'L':
	{
		bit = 2;
		break;
	}
	case 'U':
	{
		bit = 3;
		break;
	}
	}
	if (wParam == WM_KEYDOWN)
		flag |= 1 << bit;
	else
		if (wParam == WM_KEYUP)
			flag &= ~(1 << bit);
	bool lo = isSame(flag, lockmask);
	bool un = isSame(flag, unlockmask);
	if (lo && !un)
	{
		isLock = true;
	}
	if (!lo && un)
	{
		isLock = false;
	}
	if (wParam == WM_KEYDOWN && (isLock || (isLock != oldstate)))
	{
		oldstate = isLock;
		return 1;
	}

	//using oldstate to prevent sending letter 'u' in when pressing unlock-keystrokes.
	oldstate = isLock;

	return CallNextHookEx(hHook, nCode, wParam, lParam);

}



LOCK_KEYBOARD_API void setHook()
{
	if (hHook == NULL)
		hHook = SetWindowsHookEx(WH_KEYBOARD_LL, myHook, hinstlib, 0);
	if (mouseHook == NULL)
		mouseHook = SetWindowsHookEx(WH_MOUSE_LL, myHookMouse, hinstlib, 0);
	//hhHook = SetWindowsHookEx(WH_KEYBOARD, myhHook, hinstlib, 0);
	//if (hHook)
	//	MessageBox(0, L"Successfully sethook", L"", MB_OK);
}

LOCK_KEYBOARD_API void unHook()
{
	
	//UnhookWindowsHookEx(hhHook);
	if (hHook != NULL && UnhookWindowsHookEx(hHook))
	{
		hHook = NULL;
		//MessageBox(0, L"Successfully unhook", L"", MB_OK);
	}
	if (mouseHook != NULL && UnhookWindowsHookEx(mouseHook))
	{
		mouseHook = NULL;
		//MessageBox(0, L"Successfully unhook", L"", MB_OK);
	}
}