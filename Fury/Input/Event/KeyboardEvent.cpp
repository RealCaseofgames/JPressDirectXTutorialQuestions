#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent() :
	type(EventTypeInvalid),
	key(0u) {}

KeyboardEvent::KeyboardEvent(const EventType type, const UCHAR key) :
	type(type),
	key(key) {

}

bool KeyboardEvent::IsPress() const {
	return type == EventTypePress;
}

bool KeyboardEvent::IsRelease() const {
	return type == EventTypeRelease;
}

bool KeyboardEvent::IsValid() const {
	return type != EventTypeInvalid;
}

unsigned char KeyboardEvent::GetKeyCode() const {
	return key;
}