// THGK.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "THGK.h"

#define MAX_LOADSTRING 100
using namespace std;
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK QLCTProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void paintFigure(HWND hWnd, vector<wstring> loai, vector<wstring> noidung, vector<int> money);

vector<wstring> allkind;
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
	LoadString(hInstance, IDC_THGK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_THGK));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_THGK));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_THGK);
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
		DialogBox(hInst, MAKEINTRESOURCE(IDD_QLCT), hWnd, QLCTProc);

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

void SaveFile(HWND hDlg, vector<wstring> loai, vector<wstring> noidung, vector<int> money)
{
	FILE* fout;
	fout = fopen("data.txt", "w");
	
	HWND hlistdanhsach = GetDlgItem(hDlg, IDC_LIST_DANHSACH);
	int n = money.size();
	_ftprintf(fout, L"%d\n", n);
	for (int i = 0; i < n; ++i)
	{
		_ftprintf(fout, L"%s\n%s\n%d\n", loai[i].c_str(), noidung[i].c_str(), money[i]);
	}
	fclose(fout);

}
void LoadFile(HWND hDlg, vector<wstring>& loai, vector<wstring>& noidung, vector<int>& money)
{
	FILE* finp;
	TCHAR s[1111],t[1111], temp;
	finp = fopen("data.txt", "r");
	int n;
	_ftscanf(finp, L"%d", &n);
	_ftscanf(finp, L"%c", &temp);
	for (int i = 0; i < n; ++i)
	{
		int m;
		_ftscanf(finp, L"%[^\n]s", s);
		loai.push_back(wstring(s));
		_ftscanf(finp, L"%c", &temp);
		_ftscanf(finp, L"%[^\n]s", t);
		noidung.push_back(wstring(t));
		_ftscanf(finp, L"%d", &m);
		money.push_back(m);
		_ftscanf(finp, L"%c", &temp);
		


	}
	
	fclose(finp);
	int smoney = 0;
	for (int i = 0; i < n; ++i)
	{
		wsprintf(s, L"%s -- %s -- %d", loai[i].c_str(), noidung[i].c_str(), money[i]);
		SendMessage(GetDlgItem(hDlg, IDC_LIST_DANHSACH), LB_INSERTSTRING, -1, LPARAM(s));
		smoney += money[i];
	}
	SetDlgItemInt(hDlg, IDC_TONGCONG, smoney, TRUE);
}

INT_PTR CALLBACK QLCTProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	static HWND hloaichitieu = GetDlgItem(hDlg, IDC_LOAICHITIEU);
	static HWND hlistdanhsach = GetDlgItem(hDlg, IDC_LIST_DANHSACH);
	static HWND hnoidung = GetDlgItem(hDlg, IDC_NOIDUNG);
	static HWND hmoney = GetDlgItem(hDlg, IDC_SOTIEN);
	static HWND hfigure;
	static int allmoney = 0;
	static vector<wstring> aloai, anoidung;
	static vector<int> sotien;
	static bool isinit = true;
	switch (message)
	{
	case WM_INITDIALOG:
	{
		hfigure = GetDlgItem(hDlg, IDC_THGK);
		allkind.push_back(L"Eating");
		allkind.push_back(L"Transportation (bus, gas, taxi...)");
		allkind.push_back(L"Housing (fee, bill, ...)");
		allkind.push_back(L"Vehicles (fuel, maintenance...)");
		allkind.push_back(L"Supplies (soaf, ...)");
		allkind.push_back(L"Service (intenet, phone...)");
		TCHAR a[1111];
		wsprintf(a, L"Eating");
		ComboBox_AddItemData(GetDlgItem(hDlg, IDC_LOAICHITIEU), LPARAM(a));
		wsprintf(a, L"Transportation (bus, gas, taxi...)");
		ComboBox_AddItemData(GetDlgItem(hDlg,IDC_LOAICHITIEU), LPARAM(a));
		wsprintf(a, L"Housing (fee, bill, ...)");
		ComboBox_AddItemData(GetDlgItem(hDlg, IDC_LOAICHITIEU), LPARAM(a));
		wsprintf(a, L"Vehicles (fuel, maintenance...)");
		ComboBox_AddItemData(GetDlgItem(hDlg, IDC_LOAICHITIEU), LPARAM(a));
		wsprintf(a, L"Supplies (soaf, ...)");
		ComboBox_AddItemData(GetDlgItem(hDlg, IDC_LOAICHITIEU), LPARAM(a));
		wsprintf(a, L"Service (intenet, phone...)");
		ComboBox_AddItemData(GetDlgItem(hDlg, IDC_LOAICHITIEU), LPARAM(a));
		//Button_Enable(GetDlgItem(hDlg, IDC_BUTTON_DEL), FALSE);

		ComboBox_SetCurSel(hloaichitieu, 1);
		SetDlgItemText(hDlg, IDC_NOIDUNG, L"(example)");
		SetDlgItemInt(hDlg, IDC_SOTIEN, 0, TRUE);

		LoadFile(hDlg, aloai, anoidung, sotien);
		//paintFigure(hfigure, aloai, anoidung, sotien);
		//PrintFile();
		InvalidateRect(hDlg, 0, TRUE);
		UpdateWindow(hDlg);
		return (INT_PTR)TRUE;

	}
	case WM_PAINT:
	{
		if (isinit)
		{
			isinit = false;
			paintFigure(hfigure, aloai, anoidung, sotien);
		}
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDCANCEL:case IDOK:
		{
			SaveFile(hDlg, aloai, anoidung, sotien);
			EndDialog(hDlg, LOWORD(wParam));
			PostQuitMessage(0);
			return (INT_PTR)TRUE;
			break;
		}
		case IDC_BUTTON_THEM:
		{
			TCHAR loai[1111], noidung[1111];
			int money;
			GetDlgItemText(hDlg, IDC_NOIDUNG, noidung, 1111);
			money = (int)GetDlgItemInt(hDlg, IDC_SOTIEN, 0, TRUE);
			int mIndex = ComboBox_GetCurSel(GetDlgItem(hDlg, IDC_LOAICHITIEU));
			if (mIndex < 0)
				mIndex = 0;
			ComboBox_GetLBText(GetDlgItem(hDlg, IDC_LOAICHITIEU), mIndex, loai);
			TCHAR a[2222];
			wsprintf(a, L"%s  -- %s --  %d", loai, noidung, money);
			SendMessage(GetDlgItem(hDlg, IDC_LIST_DANHSACH), LB_INSERTSTRING, -1, LPARAM(a));
			
			allmoney += money;
			SetDlgItemInt(hDlg, IDC_TONGCONG, allmoney, TRUE);
			//update
			sotien.push_back(money);
			aloai.push_back(wstring(loai));
			anoidung.push_back(wstring(noidung));
			paintFigure(hfigure, aloai, anoidung, sotien);
			break;
		}
		}
		break;
	}
		break;
	}

	return (INT_PTR)FALSE;
}

COLORREF chooseColor(int c)
{
	COLORREF mcolor;
	switch (c)
	{
	case 0:
		mcolor = RGB(0, 0, 0);
		break;
	case 1:
		mcolor = RGB(0, 0, 255);
		break;
	case 2:
		mcolor = RGB(0, 255, 0);
		break;
	case 3:
		mcolor = RGB(255, 0, 255);
		break;
	case 4:
		mcolor = RGB(255, 255, 255);
		break;
	case 5:
		mcolor = RGB(0, 255, 255);
		break;
	case 6:
		mcolor = RGB(255, 0, 0);
		break;
	default:
		mcolor = RGB(255, 255, 0);
		break;
	}
	return mcolor;
}

void paintFigure(HWND hWnd, vector<wstring> loai, vector<wstring> noidung, vector<int> money)
{
	int sum[11];
	double percent[11];
	for (int i = 0; i < allkind.size(); ++i)
		sum[i] = 0;
	int n = loai.size();
	int sumall = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < allkind.size(); ++j)
			if (loai[i] == allkind[j])
				sum[j] += money[i];
		sumall += money[i];
	}
	if (sumall == 0)
	{
		for (int i = 0; i < allkind.size(); ++i)
			percent[i] = 1.0/allkind.size();
	}
	else
	{
		for (int i = 0; i < allkind.size(); ++i)
			percent[i] = 1.0*sum[i] / sumall;
	}

	HDC hdc = GetDC(hWnd);

	SelectObject(hdc, GetStockObject(DC_BRUSH));
	InvalidateRect(hWnd, 0, TRUE);
	UpdateWindow(hWnd);

	RECT client;
	GetClientRect(hWnd, &client);
	int last = 0;
	int width = client.right - client.left;
	for (int i = 0; i < allkind.size(); ++i)
	{
		int delta;
		SetDCBrushColor(hdc, chooseColor(i));
		delta = int(percent[i]*width);
		Rectangle(hdc, min(last, width), client.top, min(last + delta,width), client.bottom);
		last += delta;
	}
	ReleaseDC(hWnd, hdc);

}