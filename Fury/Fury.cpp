#include "Fury.h"

bool Fury::Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height) {
	keyboard.EnableAutoRepeatChars();
	bool ret = true;

	ret &= render_window.Initialize(this, hInstance, window_title, window_class, width, height);
	ret &= gfx.Initialize(render_window.GetWindow(), width, height);

	return ret;
}

bool Fury::ProcessMessages() {
	return render_window.ProcessMessages();
}

void Fury::Update() {
	
}

void Fury::Render() {
	gfx.Render();
}