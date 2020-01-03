#pragma once

typedef unsigned char UCHAR;

class KeyboardEvent {
public:
	enum EventType {
		EventTypePress,
		EventTypeRelease,
		EventTypeInvalid
	};

	KeyboardEvent();
	KeyboardEvent(const EventType type, const UCHAR key);
	bool IsPress() const;
	bool IsRelease() const;
	bool IsValid() const;
	unsigned char GetKeyCode() const;

private:
	EventType type;
	unsigned char key;
};