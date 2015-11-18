#include "stdafx.h"
#include "MenuProc.h"

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void allmenu::initMenu1()
{
	HMENU m = allmenu::menu[0];
	CheckMenuItem(m, ID_DRAW_ELLIPSE, MF_BYCOMMAND | MF_UNCHECKED);
	CheckMenuItem(m, ID_DRAW_RECTANGLE, MF_BYCOMMAND | MF_UNCHECKED);
	CheckMenuItem(m, ID_DRAW_LINE, MF_BYCOMMAND | MF_UNCHECKED);
	CheckMenuItem(m, ID_DRAW_PIXEL, MF_BYCOMMAND | MF_UNCHECKED);
}

void allmenu::initMenu2()
{
	HMENU m = allmenu::menu[1];
	EnableMenuItem(m, ID_EDIT_COPY, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(m, ID_EDIT_CUT, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(m, ID_EDIT_PASTE, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(m, ID_EDIT_SELECTALL, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(m, ID_FILE_OPEN32782, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(m, ID_FILE_SAVE32783, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(m, ID_FILE_SAVEAS32784, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(m, ID_FORMAT_CHOOSECOLOR32790, MF_BYCOMMAND | MF_GRAYED);
	EnableMenuItem(m, ID_FORMAT_CHOOSEFONT, MF_BYCOMMAND | MF_GRAYED);
}

LRESULT CALLBACK allmenu::menu1Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, int wmId, 
	int wmEvent, PAINTSTRUCT &ps, HINSTANCE &hInst, HDC& hdc)
{
	static DWORD itemsel = -1;
	static int olditem = itemsel;
	switch (wmId)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case IDM_FILE_NEW:
		MessageBox(hWnd, L"Ban da chon chuc nang New", L"Tool", MB_OK);
		break;
	case ID_FILE_OPEN:
		MessageBox(hWnd, L"Ban da chon chuc nang Open", L"Tool", MB_OK);
		break;
	case ID_FILE_SAVE:
		MessageBox(hWnd, L"Ban da chon chuc nang Save", L"Tool", MB_OK);
		break;
	case ID_FILE_SAVEAS:
		MessageBox(hWnd, L"Ban da chon chuc nang Save As", L"Tool", MB_OK);
		break;
	case ID_DRAW_PIXEL:
		MessageBox(hWnd, L"Ban da chon chuc nang Draw Pixel", L"Tool", MB_OK);
		itemsel = LOWORD(wParam);
		break;
	case ID_DRAW_ELLIPSE:
		MessageBox(hWnd, L"Ban da chon chuc nang Draw Ellipse", L"Tool", MB_OK);
		itemsel = LOWORD(wParam);
		break;
	case ID_DRAW_LINE:
		MessageBox(hWnd, L"Ban da chon chuc nang Draw Line", L"Tool", MB_OK);
		itemsel = LOWORD(wParam);
		break;
	case ID_DRAW_RECTANGLE:
		MessageBox(hWnd, L"Ban da chon chuc nang Draw Rectangle", L"Tool", MB_OK);
		itemsel = LOWORD(wParam);
		break;
	case ID_FORMAT_CHOOSECOLOR:
		MessageBox(hWnd, L"Ban da chon chuc nang Choose Color", L"Tool", MB_OK);
		break;
	case ID_FORMAT_CHOOSEBRUSH:
		MessageBox(hWnd, L"Ban da chon chuc nang Choose Brush", L"Tool", MB_OK);
		break;
	case ID_CHANGEMENU:
		if (SetMenu(hWnd, allmenu::menu[1]) != 0)
		{
			allmenu::currentMenu = 1;
			initMenu2();
		}
			
		
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	if (itemsel != -1)
	{
		if (GetMenuState(allmenu::menu[allmenu::currentMenu], itemsel, MF_BYCOMMAND) & MF_CHECKED)
			CheckMenuItem(allmenu::menu[allmenu::currentMenu], itemsel, MF_BYCOMMAND | MF_UNCHECKED);
		else
			CheckMenuItem(allmenu::menu[allmenu::currentMenu], itemsel, MF_BYCOMMAND | MF_CHECKED);
		if (olditem != -1 && olditem != itemsel)
			CheckMenuItem(allmenu::menu[allmenu::currentMenu], olditem, MF_BYCOMMAND | MF_UNCHECKED);
		olditem = itemsel;
		itemsel = -1;

	}
	return 0;
}

LRESULT CALLBACK allmenu::menu2Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, int wmId,
	int wmEvent, PAINTSTRUCT &ps, HINSTANCE &hInst, HDC& hdc)
{
	
	switch (wmId)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case ID_FILE_NEW:
		MessageBox(hWnd, L"Ban da chon chuc nang New", L"Tool", MB_OK);
		break;
	case ID_FILE_OPEN32782:
		MessageBox(hWnd, L"Ban da chon chuc nang Open", L"Tool", MB_OK);
		break;
	case ID_FILE_SAVE32783:
		MessageBox(hWnd, L"Ban da chon chuc nang Save", L"Tool", MB_OK);
		break;
	case ID_FILE_SAVEAS32784:
		MessageBox(hWnd, L"Ban da chon chuc nang Save As", L"Tool", MB_OK);
		break;
	case ID_EDIT_COPY:
		MessageBox(hWnd, L"Ban da chon chuc nang Copy", L"Tool", MB_OK);
		break;
	case ID_EDIT_CUT:
		MessageBox(hWnd, L"Ban da chon chuc nang Cut", L"Tool", MB_OK);
		break;
	case ID_EDIT_PASTE:
		MessageBox(hWnd, L"Ban da chon chuc nang Paste", L"Tool", MB_OK);
		break;
	case ID_EDIT_SELECTALL:
		MessageBox(hWnd, L"Ban da chon chuc nang Select All", L"Tool", MB_OK);
		break;
	case ID_FORMAT_CHOOSECOLOR32790:
		MessageBox(hWnd, L"Ban da chon chuc nang Choose Color", L"Tool", MB_OK);
		break;
	case ID_FORMAT_CHOOSEFONT:
		MessageBox(hWnd, L"Ban da chon chuc nang Choose Font", L"Tool", MB_OK);
		break;
	case ID_CHANGEMENU2:
		if (SetMenu(hWnd, allmenu::menu[0]) != 0)
		{
			allmenu::currentMenu = 0;
			initMenu1();
		}
			
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK allmenu::menuProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, int wmId,
	int wmEvent, PAINTSTRUCT &ps, HINSTANCE &hInst, HDC& hdc)
{
	switch (currentMenu)
	{
	case 0:
		return allmenu::menu1Proc(hWnd, message, wParam, lParam, wmId,
			wmEvent, ps, hInst, hdc);
		break;
	case 1:
		return allmenu::menu2Proc(hWnd, message, wParam, lParam, wmId,
			wmEvent, ps, hInst, hdc);

	}
}