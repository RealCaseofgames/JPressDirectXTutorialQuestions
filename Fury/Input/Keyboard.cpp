#include "Keyboard.h"

Keyboard::Keyboard() {
	for (int i = 0; i < 256; i++)
		keyStates[i] = false;
}

bool Keyboard::KeyIsPressed(const UCHAR keycode) {
	return keyStates[keycode];
}

bool Keyboard::KeyBufferIsEmpty() {
	return keyBuffer.empty();
}

bool Keyboard::CharBufferIsEmpty() {
	return charBuffer.empty();
}

KeyboardEvent Keyboard::ReadKey() {
	if (keyBuffer.empty())
		return KeyboardEvent();
	else {
		KeyboardEvent e = keyBuffer.front();
		keyBuffer.pop();
		return e;
	}
}

UCHAR Keyboard::ReadChar() {
	if (charBuffer.empty())
		return 0u;
	else {
		UCHAR e = charBuffer.front();
		charBuffer.pop();
		return e;
	}
}

void Keyboard::OnKeyPressed(const UCHAR key) {
	keyStates[key] = true;
	keyBuffer.push(KeyboardEvent(KeyboardEvent::EventTypePress, key));
}


void Keyboard::OnKeyReleased(const UCHAR key) {
	keyStates[key] = false;
	keyBuffer.push(KeyboardEvent(KeyboardEvent::EventTypeRelease, key));
}

void Keyboard::OnChar(const UCHAR key) {
	charBuffer.push(key);
}

void Keyboard::EnableAutoRepeatKeys() {
	autoRepeatKeys = true;
}

void Keyboard::DisableAutoRepeatKeys() {
	autoRepeatKeys = false;
}

void Keyboard::EnableAutoRepeatChars() {
	autoRepeatChars = true;
}

void Keyboard::DisableAutoRepeatChars() {
	autoRepeatChars = false;
}

bool Keyboard::IsKeysAutoRepeat() {
	return autoRepeatKeys;
}

bool Keyboard::IsCharsAutoRepeat() {
	return autoRepeatChars;
}