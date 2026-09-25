#include <input/MouseAction.hpp>

MouseAction::MouseAction(char a2, char a3, int16_t a4, int16_t a5, char a6){
	this->field_0 = a4;
	this->evButton = a2;
	this->state = a3;
	this->field_2 = a5;
	this->field_6 = 0;
	this->field_4 = 0;
	this->field_A = a6;
}

MouseAction::MouseAction(char a2, char a3, int16_t a4, int16_t a5, int16_t a6, int16_t a7, char a8){
	this->field_0 = a4;
	this->evButton = a2;
	this->state = a3;
	this->field_2 = a5;
	this->field_4 = a6;
	this->field_6 = a7;
	this->field_A = a8;
}

bool_t MouseAction::isButton() const{
	return (uint32_t)(uint8_t)this->evButton - 1 <= 1;
}
