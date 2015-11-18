// Homework - 1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Homework - 1.h"

#define MAX_LOADSTRING 200

// Global Variables:
HINSTANCE hInst;						// current instance
TCHAR szTitle[MAX_LOADSTRING];			// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];	// the main window class name
TCHAR szClient[MAX_LOADSTRING];

// Forward declarations of functions included in this code module:
//Prototype của các hàm xử lý
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;				//Biến lưu trữ thông tin sự kiện
	HACCEL hAccelTable;		//Bảng phím tắt cho các menu item

	// Initialize global strings
	//Khởi tạo các biến chuỗi toàn cục
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);			//Lấy tên tiêu đề
	LoadString(hInstance, IDC_HOMEWORK1, szWindowClass, MAX_LOADSTRING);	//Lấy tên class, sau này khi ta thao tác với nhiều đối tượng khác nhau
																			//thì mỗi đối tượng thường có các window khác nhau
	LoadString(hInstance, IDC_CLIENT, szClient, MAX_LOADSTRING);			//Lấy nội dung vùng client (myCode)
	MyRegisterClass(hInstance);												//Đăng ký lớp cửa sổ cho ứng dụng

	// Perform application initialization:
	//Khởi tạo ứng dụng
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	//Khởi tạo bảng phím tắt cho các menu item
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOMEWORK1));

	// Main message loop:
	//Vòng lặp tiếp nhận và xử lý thông điệp
	while (GetMessage(&msg, NULL, 0, 0))	//Lấy các bản tin từ message queue
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);		//Dịch virtual-key message thành character message
			DispatchMessage(&msg);		//Phát sinh message đến window produce (hàm WndProc)
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//Đăng ký lớp cho cửa sổ chính
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);					//Kích thước trên bộ nhớ của window class này

	wcex.style			= CS_HREDRAW | CS_VREDRAW;		//Kiểu của Class
														//CS_VREDRAW: Vẽ lại vùng entire khi chiều cao của window bị thay đổi
														//CS_HREDRAW: Vẽ lại vùng entire khi chiều rộng của window bị thay đổi
	wcex.lpfnWndProc	= WndProc;						//Thủ tục của window (window procedure) là con trỏ trỏ tới WinProc khi bắt đầu vòng lặp thông tin sự kiện
	wcex.cbClsExtra		= 0;							//Số lượng dữ liệu tối đa được cài đặt cho class này, thường là 0
	wcex.cbWndExtra		= 0;							//Tương tự
	wcex.hInstance		= hInstance;					//Quản lý thông tin của cửa sổ
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOMEWORK1));		//Icon lớn của class này
	wcex.hCursor		= LoadCursor(NULL, IDC_CROSS);								//Con trỏ chuột của class
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);									//Màu nền của class
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_HOMEWORK1);							//Con trỏ trỏ về dữ liệu của các thanh menu
	wcex.lpszClassName	= szWindowClass;											//Tên của class này
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));		//Icon nhỏ của class này

	return RegisterClassEx(&wcex);						//Đăng ký class
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

   hInst = hInstance; // Store instance handle in our global variable - Lưu trữ biến instance handle vào biến toàn cục

   hWnd = CreateWindow(
	   szWindowClass,			//Tên class
	   szTitle,					//Tiêu đề
	   WS_OVERLAPPEDWINDOW,		//Kiểu, ở đây tương đương với (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
	   CW_USEDEFAULT, 0,		//Tọa độ góc trái trên của cửa sổ khi bắt đầu phần mềm
	   CW_USEDEFAULT, 0,		//Chiều rộng và chiều cao của cửa sổ
	   NULL,					//Cửa sổ cha (vì ở đây là cửa sổ đầu tiên nên gán NULL)
	   NULL,					//Handle của menu chương trình
	   hInstance,				//Instance của chương trình
	   NULL);					//Con trỏ các thông tin bổ sung

   //Thoát nếu không tạo cửa sổ thành công
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);	//Hiển thị cửa sổ, nếu không lệnh này thì chương trình vẫn chạy trong Task Manager nhưng không thấy cửa sổ
   UpdateWindow(hWnd);			//Vẽ lại nội dung vùng client

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

//Hàm nhận và xử lý thông điệp cho cửa sổ giao diện chính
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	
	TCHAR str[100];	//Chuỗi để xử lý cho hiển thị các hộp thông báo (myCode)
	switch (message)
	{
	case WM_CREATE:		//Bắt đầu chương trình
		MessageBox(hWnd, _T("Chào mừng bạn đến với chương trình Demo1\nTác giả: Nguyễn Hoàng Phương\nHãy nhấn OK để tiếp tục thực hiện chương trình."), _T("Giới thiệu"), MB_ICONINFORMATION | MB_OK);
		break;
	case WM_LBUTTONDOWN: case WM_RBUTTONDOWN:	//Khi có thao tác nhấn chuột (trái hoặc phải)
		if (wParam == MK_LBUTTON)
			_stprintf(str, _T("Bạn vừa nhấn nút trái mouse\nTại tọa độ X=%d Y=%d"), LOWORD(lParam), HIWORD(lParam));
		else
		if (wParam == MK_RBUTTON)
			_stprintf(str, _T("Bạn vừa nhấn nút phải mouse\nTại tọa độ X=%d Y=%d"), LOWORD(lParam), HIWORD(lParam));
		else
			break;
		
		MessageBox(hWnd, str, _T("Thông báo"), MB_ICONINFORMATION | MB_OK);
		break;
	case WM_COMMAND:	//Người sử dụng click một mục trên menu, button
		wmId    = LOWORD(wParam);	//Lấy id của menu được chọn
		wmEvent = HIWORD(wParam);	//wmEvent = 1 nghĩa là đang sử dụng phím tắt
		// Parse the menu selections:
		switch (wmId)
		{
		//Dựa vào tham số wmId để xử lý cho từng menu item được chọn
		case ID_FILE_NEW:
			MessageBox(hWnd, _T("Bạn vừa chọn chức năng New."), _T("Thông báo"), MB_ICONINFORMATION | MB_OK);
			break;
		case ID_FILE_OPEN:
			MessageBox(hWnd, _T("Bạn vừa chọn chức năng Open."), _T("Thông báo"), MB_ICONINFORMATION | MB_OK);
			break;
		case ID_FILE_SAVE:
			MessageBox(hWnd, _T("Bạn vừa chọn chức năng Save."), _T("Thông báo"), MB_ICONINFORMATION | MB_OK);
			break;
		case ID_EDIT_UNDO:
			MessageBox(hWnd, _T("Bạn vừa chọn chức năng Undo."), _T("Thông báo"), MB_ICONINFORMATION | MB_OK);
			break;
		case ID_EDIT_CUT:
			MessageBox(hWnd, _T("Bạn vừa chọn chức năng Cut."), _T("Thông báo"), MB_ICONINFORMATION | MB_OK);
			break;
		case ID_EDIT_COPY:
			MessageBox(hWnd, _T("Bạn vừa chọn chức năng Copy."), _T("Thông báo"), MB_ICONINFORMATION | MB_OK);
			break;
		case ID_EDIT_PASTE:
			MessageBox(hWnd, _T("Bạn vừa chọn chức năng Paste."), _T("Thông báo"), MB_ICONINFORMATION | MB_OK);
			break;
		case ID_EDIT_SELECTALL:
			MessageBox(hWnd, _T("Bạn vừa chọn chức năng Select All."), _T("Thông báo"), MB_ICONINFORMATION | MB_OK);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			SendMessage(hWnd, WM_CLOSE, wParam, lParam);	//Chuyển sự kiện chọn menu item Exit sang để cho WM_CLOSE xử lý
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...

		RECT rt;
		GetClientRect(hWnd, &rt);
		DrawText(hdc, szClient, wcslen(szClient), &rt, DT_CENTER);

		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, _T("Bạn muốn kết thúc chương trình ?"), _T("Xác nhận"), MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
			DestroyWindow(hWnd);
		break;
	case WM_DESTROY:			//Sự kiện xảy ra khi có lệnh đóng chương trình - xóa các con của cửa sổ này trước khi thực hiện lệnh kế tiếp
		PostQuitMessage(0);		//Gửi bản tin WM_QUIT tới hàng đợi thông điệp để chờ xử lí
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
