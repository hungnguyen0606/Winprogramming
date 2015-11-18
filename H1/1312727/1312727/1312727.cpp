// 1312727.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1312727.h"

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

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//UNREFERENCED_PARAMETER(hPrevInstance);
	//UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY1312727, szWindowClass, MAX_LOADSTRING);
	//đăng ký, khởi tạo các thông tin cơ bản của lớp cửa sổ: hàm xử lý msg, con trỏ, ...
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		//nếu không khởi tạo được thông số ứng dụng thì thoát chương trình
		return FALSE;
	}

	//load các phím tắt
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1312727));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//Kiểm tra phím tắt. Nếu đúng gửi thông điệp trực tiếp tới hàm xử lý
		//ngược lại thực thi 2 hàm translatemessage và dispatchmessage
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			//gọi hàm xử lý thông điệp
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

	//kích thước tính theo byte của class
	wcex.cbSize = sizeof(WNDCLASSEX);

	//định kiểu của class: mỗi kiểu sẽ định nghĩa các thành phần cơ bản khác
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	//khởi tạo con trỏ với hàm xử lý thông điệp tương ứng
	wcex.lpfnWndProc	= WndProc;
	//
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	//handle của instance chứa hàm xử lý cửa sổ của lớp.
	wcex.hInstance		= hInstance;
	//load icon của chương trình từ resources và trả về handle
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1312727));
	//load con trỏ của ctr và trả về handle
	wcex.hCursor		= LoadCursor(NULL, IDC_CROSS);
	//gán giá trị màu nền của ctr hoặc handle của brush dùng để vẽ nền
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	//khởi tạo tên của resource của lớp menu 
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY1312727);
	//tên của lớp cửa sổ dc đăng ký hoặc con trỏ tới lớp atom được tạo bởi RegisterClass
	wcex.lpszClassName	= szWindowClass;
	//load small icon của ứng dụng và trả về handle của icon tương ứng
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
   
   //tạo cửa sổ với các thông số mặc định và trả về window handle
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   //nếu giá trị hWnd là null - không tạo được cửa sổ thì return false.
   if (!hWnd)
   {
      return FALSE;
   }

   //hiển thị và cập nhật cửa sổ
   ShowWindow(hWnd, nCmdShow);
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
		//loại thông điệp tương ứng với menu hay phím tắt được sử dụng
		wmId    = LOWORD(wParam);
		//loại sự kiện: 0-từ menu, 1-phím tắt
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
//#define IDM_NEW					201
//#define IDM_OPEN				202
//#define IDM_SAVE				203
//#define IDM_UNDO				204
//#define IDM_CUT					205
//#define IDM_PASTE				206
//#define IDM_SELECTALL			207
//#define IDM_COPY	
		case IDM_NEW:
			MessageBox(hWnd, _T("Ban vua chon chuc nang NEW"), _T("Default"), MB_OK);
			break;
		case IDM_OPEN:
			MessageBox(hWnd, _T("Ban vua chon chuc nang OPEN"), _T("Default"), MB_OK);
			break;
		case IDM_SAVE:
			MessageBox(hWnd, _T("Ban vua chon chuc nang SAVE"), _T("Default"), MB_OK);
			break;
		case IDM_UNDO:
			MessageBox(hWnd, _T("Ban vua chon chuc nang UNDO"), _T("Default"), MB_OK);
			break;
		case IDM_CUT:
			MessageBox(hWnd, _T("Ban vua chon chuc nang CUT"), _T("Default"), MB_OK);
			break;
		case IDM_PASTE:
			MessageBox(hWnd, _T("Ban vua chon chuc nang PASTE"), _T("Default"), MB_OK);
			break;
		case IDM_SELECTALL:
			MessageBox(hWnd, _T("Ban vua chon chuc nang SELECT ALL"), _T("Default"), MB_OK);
			break;
		case IDM_COPY:
			MessageBox(hWnd, _T("Ban vua chon chuc nang COPY"), _T("Default"), MB_OK);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
		{
			//char x[11] = "23";
			
			int msgId = MessageBox(hWnd, _T("Ban muon thoat ung dung"), _T("EXIT"), MB_YESNO);
			if (msgId == IDYES)
				DestroyWindow(hWnd);
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONUP:
	{
		int xPos = LOWORD(lParam);
		int yPos = HIWORD(lParam);
		std::stringstream out;
		out << "Ban vua nhan nut trai mouse\nTai toa do X=" << xPos << " Y=" << yPos;
		std::string temp = out.str();
		MessageBox(hWnd, std::wstring(temp.begin(), temp.end()).c_str(), _T("Thong bao"), MB_OK);
		break;
	}
		
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		std::stringstream out;
		out << "Day la chuong trinh dau tien..." << "\n";
		out << "...viet bang Visual C++..." << "\n";
		out << "...bang thu vien Win32 API..."<< "\n";
		std::string temp = out.str();
		std::wstring strHello(temp.begin(), temp.end());
		//--------------------
		RECT *client = new RECT();
		RECT *t = new RECT();
		
		//calculate the size of the rectangle wrapping the text but not draw the text
		DrawText(hdc, strHello.c_str(), strHello.length(), t, DT_CALCRECT);
		
		//get window's size
		GetClientRect(hWnd, client);
		//move the rect to the window's center
		OffsetRect(t, (client->right - t->right)/2, (client->bottom - t->bottom)/2);

		//draw the text
		DrawText(hdc, strHello.c_str(), strHello.length(), t, DT_TOP);
		
		delete t;
		delete client;
		
		EndPaint(hWnd, &ps);
	}
		
	break;
		
	case WM_CREATE:
		MessageBox(hWnd, _T("Chao mung den voi chuong trinh Demo 1.\nTac gia: Nguyen Phan Manh Hung\nHay nhan OK de tiep tuc thuc hien chuong trinh."), _T("Gioi thieu"), MB_OK);
		break;
	case WM_DESTROY:
		//gửi thông điệp tắt ứng dụng vào hàng đợi
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
