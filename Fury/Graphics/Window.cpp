#include "WindowContainer.h"

bool Window::Initialize(WindowContainer *pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height) {
	this->hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide(this->window_title);
	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide(this->window_class);

	RegisterWindowClass();

	handle = CreateWindowEx(0,
		window_class_wide.c_str(),
		window_title_wide.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		(GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - height) / 2,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		pWindowContainer);

	if (handle == NULL) {
		ErrorLogger::Log(GetLastError(), "CreateWindowEX Failed for window: " + window_title);
		return false;
	}

#ifdef _DEBUG
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif // _DEBUG

	ShowWindow(handle, SW_SHOW);
	SetForegroundWindow(handle);
	SetFocus(handle);

	return true;
}

bool Window::ProcessMessages() {
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (PeekMessage(&msg, handle, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_NULL) {
		if (!IsWindow(handle)) {
			handle = NULL;
			UnregisterClass(window_class_wide.c_str(), hInstance);
			return false;
		}
	}
	
	return true;
}

HWND Window::GetWindow() {
	return handle;
}

Window::~Window() {
	if (handle != NULL) {
		UnregisterClass(window_class_wide.c_str(), hInstance);
		DestroyWindow(handle);
	}
}

LRESULT APIENTRY HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
		return 0;
	}
	default:
	{
		WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}

LRESULT APIENTRY HandleMsgSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowContainer *pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (pWindow == nullptr) {
			ErrorLogger::Log("Critical Error: Pointer to window container is null during WM_NCCREATE.");
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}

void Window::RegisterWindowClass() {
	WNDCLASSEX wc;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = window_class_wide.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&wc);
}