// DLL_HOOK.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DLL_HOOK.h"

BOOL  g_bBeep = FALSE;
HINSTANCE hinstlib;
HHOOK hHook, hhHook;
bool isLock = false;
bool oldstate = false;
int flag = 0;
const int lockmask = 7;
const int unlockmask = 11;
// This is an example of an exported variable
DLL_HOOK_API int nDLL_HOOK=0;

// This is an example of an exported function.
DLL_HOOK_API int fnDLL_HOOK(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see DLL_HOOK.h for the class definition
CDLL_HOOK::CDLL_HOOK()
{
	return;
}

int cc = 0;

bool isSame(int state, int mask)
{
	if ((state & mask) == mask && (state & (~mask)) == 0)
		return true;
	return false;
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
			case 'K':
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



DLL_HOOK_API void setHook()
{
	if (hHook != NULL)
		return;
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, myHook, hinstlib, 0);
	//hhHook = SetWindowsHookEx(WH_KEYBOARD, myhHook, hinstlib, 0);
	if (hHook)
		MessageBox(0, L"Successfully sethook", L"", MB_OK);
}

DLL_HOOK_API void unHook()
{
	if (hHook == NULL)
		return;
	//UnhookWindowsHookEx(hhHook);
	if (UnhookWindowsHookEx(hHook))
	{
		hHook = NULL;
		MessageBox(0, L"Successfully unhook", L"", MB_OK);
	}
}