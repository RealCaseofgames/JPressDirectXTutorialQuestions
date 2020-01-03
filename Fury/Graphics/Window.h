#pragma once

#include "../Util/ErrorLogger.h"

class WindowContainer;

class Window
{
public:
	bool Initialize(WindowContainer *pWindowContainer, HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();
	HWND GetWindow();
	~Window();
private:
	void RegisterWindowClass();
	HWND handle = NULL; // Window Handle Object
	HINSTANCE hInstance = NULL; //Instance Handle Object
	std::string window_title = "";
	std::wstring window_title_wide = L"";
	std::string window_class = "";
	std::wstring window_class_wide = L"";
	int width = 0;
	int height = 0;
};