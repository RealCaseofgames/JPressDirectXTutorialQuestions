#include "MouseEvent.h"

MouseEvent::MouseEvent() :
	type(EventTypeInvalid),
	x(0),
	y(0) {}

MouseEvent::MouseEvent(EventType type, int x, int y) :
	type(type),
	x(x),
	y(y) {}

bool MouseEvent::IsValid() const {
	return type != EventTypeInvalid;
}

MouseEvent::EventType MouseEvent::GetType() const {
	return type;
}

MousePoint MouseEvent::GetPos() const {
	return { x, y };
}

int MouseEvent::GetPosX() const {
	return x;
}

int MouseEvent::GetPosY() const {
	return y;
}