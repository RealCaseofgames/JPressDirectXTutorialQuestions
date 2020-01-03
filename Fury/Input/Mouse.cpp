#include "Mouse.h"

void Mouse::OnLeftPressed(int x, int y)
{
	leftIsDown = true;
	MouseEvent me(MouseEvent::EventTypeLPress, x, y);
	eventBuffer.push(me);
}

void Mouse::OnLeftReleased(int x, int y)
{
	leftIsDown = false;
	eventBuffer.push(MouseEvent(MouseEvent::EventTypeLRelease, x, y));
}

void Mouse::OnRightPressed(int x, int y)
{
	rightIsDown = true;
	eventBuffer.push(MouseEvent(MouseEvent::EventTypeRPress, x, y));
}

void Mouse::OnRightReleased(int x, int y)
{
	rightIsDown = false;
	eventBuffer.push(MouseEvent(MouseEvent::EventTypeRRelease, x, y));
}

void Mouse::OnMiddlePressed(int x, int y)
{
	mbuttonDown = true;
	eventBuffer.push(MouseEvent(MouseEvent::EventTypeMPress, x, y));
}

void Mouse::OnMiddleReleased(int x, int y)
{
	mbuttonDown = false;
	eventBuffer.push(MouseEvent(MouseEvent::EventTypeMRelease, x, y));
}

void Mouse::OnWheelUp(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventTypeWheelUp, x, y));
}

void Mouse::OnWheelDown(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventTypeWheelDown, x, y));
}

void Mouse::OnMouseMove(int x, int y)
{
	x = x;
	y = y;
	eventBuffer.push(MouseEvent(MouseEvent::EventTypeMove, x, y));
}

void Mouse::OnMouseMoveRaw(int x, int y) {

	eventBuffer.push(MouseEvent(MouseEvent::EventTypeRawMove, x, y));
}

bool Mouse::IsLeftDown()
{
	return leftIsDown;
}

bool Mouse::IsMiddleDown()
{
	return mbuttonDown;
}

bool Mouse::IsRightDown()
{
	return rightIsDown;
}

int Mouse::GetPosX()
{
	return x;
}

int Mouse::GetPosY()
{
	return y;
}

MousePoint Mouse::GetPos()
{
	return{ x, y };
}

bool Mouse::EventBufferIsEmpty()
{
	return eventBuffer.empty();
}

MouseEvent Mouse::ReadEvent()
{
	if (eventBuffer.empty())
	{
		return MouseEvent();
	}
	else
	{
		MouseEvent e = eventBuffer.front(); //Get first event from buffer
		eventBuffer.pop(); //Remove first event from buffer
		return e;
	}
}