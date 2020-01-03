#pragma once

struct MousePoint {
	int x, y;
};

class MouseEvent
{
public:
	enum EventType
	{
		EventTypeLPress,
		EventTypeLRelease,
		EventTypeRPress,
		EventTypeRRelease,
		EventTypeMPress,
		EventTypeMRelease,
		EventTypeWheelUp,
		EventTypeWheelDown,
		EventTypeMove,
		EventTypeRawMove,
		EventTypeInvalid
	};
private:
	EventType type;
	int x, y;
public:
	MouseEvent();
	MouseEvent(const EventType type, const int x, const int y);
	bool IsValid() const;
	EventType GetType() const;
	MousePoint GetPos() const;
	int GetPosX() const;
	int GetPosY() const;
};