#pragma once

#include "Window.h"
#include "../Input/Keyboard.h"
#include "../Input/Mouse.h"
#include "Graphics.h"

class WindowContainer {
public:
	WindowContainer();
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	Window render_window;
	Keyboard keyboard;
	Mouse mouse;
	Graphics gfx;
private:
};