// H14.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "H14.h"
#include <Windowsx.h>
#include <Shlwapi.h>
#include <commdlg.h>
#include <Shlobj.h>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//-------------------------------------------------
void copyTo(LPVOID dat);
bool isValidPath(TCHAR path[]);
bool mergeFiles();
INT_PTR CALLBACK CopyDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
//----------------------------------------------------
struct data
{
	TCHAR* source;
	TCHAR* destination;
	DWORD idviewer;
};
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_H14, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_H14));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H14));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_H14);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   //ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CREATE:
	{
		DialogBox(hInst, MAKEINTRESOURCE(IDD_COPY), hWnd, CopyDialog);
		SendMessage(hWnd, WM_DESTROY, 0, 0);
		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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

INT_PTR CALLBACK CopyDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		/*HWND combo = GetDlgItem(hDlg, IDC_COMBO_THREAD);
		ComboBox_AddString(combo, L"1");
		ComboBox_AddString(combo, L"2");
		ComboBox_AddString(combo, L"3");
		ComboBox_AddString(combo, L"4");
		ComboBox_AddString(combo, L"5");*/
		return (INT_PTR)TRUE;
	}
		

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_SOURCE:
		{
			OPENFILENAME ofn; // CTDL dùng cho dialog open
			TCHAR szFile[1024];
			//TCHAR *szFilter = NULL;
			szFile[0] = '\0';
			// Khởi tạo struct
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hDlg; // handle của window cha
			ofn.lpstrFilter = NULL;
			ofn.nFilterIndex = 1;
			ofn.lpstrFile = szFile; // chuỗi tên file trả về
			ofn.nMaxFile = sizeof(szFile);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			BOOL a;
			a = GetOpenFileName(&ofn);
			if (a)
			{
				Edit_SetText(GetDlgItem(hDlg, IDC_SOURCE), szFile);
			}
			break;
		}
		
		case IDC_BUTTON_DESTINATION:
		{
			TCHAR path[1024];// , pt[1024];
			path[0] = 0;
			BROWSEINFO br;
			br.hwndOwner = hDlg;
			br.pidlRoot = NULL;
			br.pszDisplayName = NULL;
			br.lpfn = NULL;
			br.lpszTitle = NULL;
			br.ulFlags = 0;
			PCIDLIST_ABSOLUTE id;
			id = SHBrowseForFolder(&br);
			SHGetPathFromIDList(id, path);
			if (id != NULL)
			{
				Edit_SetText(GetDlgItem(hDlg, IDC_DESTINATION), path);
			}
			break;
		}
		case IDC_BUTTON_COPY:
		{
			TCHAR source[1024], destination[1024];
			HANDLE threadHandle[5];
			int threadId[5];
			GetDlgItemText(hDlg, IDC_SOURCE, source, 1023);
			GetDlgItemText(hDlg, IDC_DESTINATION, destination, 1023);
			int numThread = 0;

			//error handle
			if (!isValidPath(source) || (GetFileAttributes(source)&FILE_ATTRIBUTE_DIRECTORY))
			{
				MessageBox(hDlg, L"Invalid file.", L"Error", MB_OK);
				break;
			}

			if (!isValidPath(destination) || (GetFileAttributes(destination)&FILE_ATTRIBUTE_DIRECTORY)==0)
			{
				MessageBox(hDlg, L"Invalid destination folder.", L"Error", MB_OK);
				break;
			}
			numThread = (int)GetDlgItemInt(hDlg, IDC_NUMTHREAD, 0, TRUE);
			if (numThread < 1 || numThread > 5)
			{
				MessageBox(hDlg, L"The number of threads must be between 1-5.", L"Error", MB_OK);
				break;
			}
			//-------
			
			for (int i = 0; i < numThread; ++i)
			{
				threadHandle[i] = CreateThread(NULL, 1024, (LPTHREAD_START_ROUTINE)copyTo, NULL, 0, (LPDWORD) &threadId[i]);
				if (threadHandle[i] == NULL)
				{
					MessageBox(hDlg, L"Cannot create enough threads to copy.", L"Error", MB_OK);
					return (INT_PTR)TRUE;
				}
			}

			DWORD Status = WaitForMultipleObjects(numThread, threadHandle, TRUE, INFINITE);
			bool isMerged = mergeFiles();

			if (!isMerged)
			{
				MessageBox(hDlg, L"Fail to merge files.", L"Error", MB_OK);
			}
			else
			{
				MessageBox(hDlg, L"Copy successfully.", L"Error", MB_OK);
			}
			break;
		}
		

		default: return (INT_PTR)TRUE;
		}
		break;
	}
		
	}
	return (INT_PTR)FALSE;
}

int getNumThread(HWND hDlg)
{
//	HWND combo = GetDlgItem(hDlg, IDC_COMBO_THREAD);
	return 0;
}
void copyTo(LPVOID dat)
{
	ExitThread(0);
}

bool mergeFiles()
{
	return true;
}

bool isValidPath(TCHAR path[])
{
	return PathFileExists(path);
	return true;
}