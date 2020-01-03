#include "Fury/Fury.h"

int APIENTRY wWinMain(
	_In_ HINSTANCE		hInstance,
	_In_opt_ HINSTANCE	hPrevInstance,
	_In_ LPTSTR			lpCmdLine,
	_In_ int			nCmdShow
) {
	Fury fury;
	if (fury.Initialize(hInstance, "Arbitrary Window Title", "WindowClass", 800, 600)) {
		while (fury.ProcessMessages()) {
			fury.Update();
			fury.Render();
		}
	}

	return 0;
}