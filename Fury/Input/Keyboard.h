#pragma once

#include "Event/KeyboardEvent.h"
#include <queue>

class Keyboard {
public:
	Keyboard();
	bool KeyIsPressed(const UCHAR keycode);
	bool KeyBufferIsEmpty();
	bool CharBufferIsEmpty();
	KeyboardEvent ReadKey();
	UCHAR ReadChar();
	void OnKeyPressed(const UCHAR key);
	void OnKeyReleased(const UCHAR key);
	void OnChar(const UCHAR key);
	void EnableAutoRepeatKeys();
	void DisableAutoRepeatKeys();
	void EnableAutoRepeatChars();
	void DisableAutoRepeatChars();
	bool IsKeysAutoRepeat();
	bool IsCharsAutoRepeat();
private:
	bool autoRepeatKeys = false;
	bool autoRepeatChars = false;
	bool keyStates[256];
	std::queue<KeyboardEvent> keyBuffer;
	std::queue<UCHAR> charBuffer;
};