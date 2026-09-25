#pragma once
#include <_types.h>

struct MouseAction{
	int16_t field_0;
	int16_t field_2;
	int16_t field_4;
	int16_t field_6;
	char evButton;
	char state;
	char field_A;

	MouseAction(char, char, int16_t, int16_t, char);
	MouseAction(char, char, int16_t, int16_t, int16_t, int16_t, char);
	bool_t isButton() const;
};
