#include"MainWindow.h"
#include <assert.h>
#include <exception>
#include "resource.h"
#include <sstream>

MainWindow::MainWindow(HINSTANCE hInst, wchar_t* pArgs)
	:
	args(pArgs),
	hInst(hInst)
{
	// register window class
	WNDCLASSEX wc = { sizeof(WNDCLASSEX),CS_CLASSDC,_HandleMsgSetup,0,0,
		hInst,nullptr,nullptr,nullptr,nullptr,
		wndClassName,nullptr };
	wc.hIconSm = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
	wc.hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	RegisterClassEx(&wc);

	// create window & get hWnd
	RECT wr;
	wr.left = 600;
	wr.right = Graphics::ScreenWidth + wr.left;
	wr.top = 500;
	wr.bottom = Graphics::ScreenHeight + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	hWnd = CreateWindow(wndClassName, L"Mario",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, hInst, this);

	// throw exception if something went terribly wrong
	if (hWnd == nullptr)
	{
		throw "Failed to get valid window handle.";
	}

	// show and update
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
}

MainWindow::~MainWindow()
{
	// unregister window class
	UnregisterClass(wndClassName, hInst);
}

bool MainWindow::IsActive() const
{
	return GetActiveWindow() == hWnd;
}

bool MainWindow::IsMinimized() const
{
	return IsIconic(hWnd) != 0;
}

void MainWindow::ShowMessageBox(const std::wstring & title, const std::wstring& message) const
{
	MessageBox(hWnd, message.c_str(), title.c_str(), MB_OK);
}

bool MainWindow::ProcessMessage()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			return false;
		}
	}
	return true;
}

LRESULT WINAPI MainWindow::_HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		MainWindow* const pWnd = reinterpret_cast<MainWindow*>(pCreate->lpCreateParams);
		// sanity check
		assert(pWnd != nullptr);
		// set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&MainWindow::_HandleMsgThunk));
		// forward message to window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI MainWindow::_HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// retrieve ptr to window class
	MainWindow* const pWnd = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window class handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT MainWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		// ************ KEYBOARD MESSAGES ************ //
	case WM_KEYDOWN:
		if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled()) // no thank you on the autorepeat
		{
			kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	case WM_KEYUP:
		kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		kbd.OnChar(static_cast<unsigned char>(wParam));
		break;
		// ************ END KEYBOARD MESSAGES ************ //
	/*case WM_MOUSEMOVE:
		const POINTS pt = MAKEPOINTS(lParam);
		std::wostringstream oss;
		oss << L"(" << pt.x << L"," << pt.y << L")";
		SetWindowText(hWnd,oss.str().c_str());*/
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}