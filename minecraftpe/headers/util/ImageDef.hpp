#pragma once
#include <_types.h>
#include <string>

struct ImageDef{
	std::string field_0;
	int32_t field_4, field_8;
	float width, height;
	int32_t field_14, field_18, field_1C, field_20;
	int8_t field_24, field_25, field_26, field_27;

	ImageDef() {
		this->field_4 = 0;
		this->field_8 = 0;
		this->field_14 = 0;
		this->width = 16;
		this->height = 16;
		this->field_18 = 0;
		this->field_1C = 1;
		this->field_20 = 1;
		this->field_24 = 0;
	}
};

