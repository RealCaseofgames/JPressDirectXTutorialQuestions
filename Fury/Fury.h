#pragma once

#include "Graphics/WindowContainer.h"

class Fury : WindowContainer {
public:
	bool Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();
	void Update();
	void Render();
};