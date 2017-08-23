// GT_HelloWorldWin32.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("syncro");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Assignment 4 - syncro");

HINSTANCE hInst;
HANDLE hEvents[2];
DWORD i, dwEvent;
HANDLE hMutex;
HWND hWnd;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	for (int i = 0; i < 2; i++) {
		hEvents[i] = CreateEvent(NULL, FALSE, FALSE, TEXT("sync"));
		if (hEvents[i] == NULL) {
			MessageBox(NULL, L"Error Occured - Event is equal to NULL", L"Assignment 4 Error", MB_OK);
		}
	}
	hEvents[0] = CreateEvent(NULL, TRUE, FALSE, TEXT("Button2"));
	hEvents[1] = CreateEvent(NULL, TRUE, FALSE, TEXT("Button3"));

	dwEvent = WaitForMultipleObjects(2, hEvents, FALSE, INFINITE);

	switch (dwEvent) {
	case WAIT_OBJECT_0 + 0:
		hWnd = CreateWindow(szWindowClass,                  // window class name
		TEXT("Program 2 Started"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style
		0,              // initial x position
		0,              // initial y position
		1200,              // initial x size
		800,              // initial y size
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);
		break;

	case WAIT_OBJECT_0 + 1:
		hWnd = CreateWindow(szWindowClass,                  // window class name
		TEXT("Program 3 Started"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style
		0,              // initial x position
		0,              // initial y position
		1200,              // initial x size
		800,              // initial y size
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);
		break;

	default:
		MessageBox(NULL, L"Wait error", L"Assignment 4 Error", MB_OK);
		ExitProcess(0);

	}

#ifdef DEBUG
	int MessageLoop(
		HANDLE* lphObjects, //handles that need to be waited on
		int cObjects);//number of handles to wait on
	{
		while (TRUE)
		{
			//block-local variable
			DWORD result;
			MSG msg;

			int i = sizeof(hEvents);

			//empty msg queue otherwise we will immediately stop waiting in MsgWaitFor...
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					return 1;
				DispatchMessage(&msg);
			}

			//block until either any object signals or a msg is put in the msg //queue
			result = MsgWaitForMultipleObjects(cObjects, lphObjects, FALSE, INFINITE, QS_ALLINPUT);

			//indicates a msg is in the queue
			if (result == (WAIT_OBJECT_0 + cObjects))
			{
				continue;//will loop back up to PeekMessage to process msg
			}
			else
			{
				//object signaling, result-WAIT... = id
				//Other Code(result - WAIT_OBJECT_0);
			}
		}//end while
	} // end message loop    
#endif // DEBUG

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// Jason Chan - Change background colour to red
	wcex.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable

					   // The parameters to CreateWindow explained:
					   // szWindowClass: the name of the application
					   // szTitle: the text that appears in the title bar
					   // WS_OVERLAPPEDWINDOW: the type of window to create
					   // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
					   // 500, 500: initial size (width, length)
					   // NULL: the parent of this window
					   // NULL: this application does not have a menu bar
					   // hInstance: the first parameter from WinMain
					   // NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// Jason Chan - Red button created
	HWND hwndButtonRed = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"Red Car",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10,         // x position 
		10,         // y position 
		100,        // Button width
		25,        // Button height
		hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	// Jason Chan - Blue button created
	HWND hwndButtonBlue = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"Blue Car",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10,         // x position 
		60,         // y position 
		100,        // Button width
		25,        // Button height
		hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.
	
	// Jason Chan - Green button created
	HWND hwndButtonGreen = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"Green Car",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10,         // x position 
		110,         // y position 
		100,        // Button width
		25,        // Button height
		hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	// Jason Chan - Orange button created
	HWND hwndButtonOrange = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"Orange Car",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10,         // x position 
		160,         // y position 
		100,        // Button width
		25,        // Button height
		hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	// Jason Chan - Black button created
	HWND hwndButtonBlack = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"Black Car",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		10,         // x position 
		210,         // y position 
		100,        // Button width
		25,        // Button height
		hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	//TCHAR greeting[] = _T("Hello, World!");
	static int cxClient, cyClient;

	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		MoveToEx(hdc, cxClient /2, 0, NULL);
		LineTo(hdc, cxClient/2, cyClient);
		// Here your application is laid out.
		// For this introduction, we just print out "Hello, World!"
		// in the top left corner.
		//TextOut(hdc,
			//5, 5,
			//greeting, _tcslen(greeting));
		// End application-specific layout section.

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}