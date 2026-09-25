#pragma once
#include <_types.h>
#include <string>

struct GuiMessage
{
	int32_t field_0, field_4;
	std::string field_8, field_C, field_10;

	GuiMessage(const GuiMessage& a2)
		: field_0(a2.field_0)
		, field_4(a2.field_4)
		, field_8(a2.field_8)
		, field_C(a2.field_C)
		, field_10(a2.field_10) {
	}
	GuiMessage(GuiMessage&& a2)
		: field_0(a2.field_0)
		, field_4(a2.field_4)
		, field_8(std::move(a2.field_8))
		, field_C(std::move(a2.field_C))
		, field_10(std::move(a2.field_10)) {
	}
	GuiMessage(const std::string& a2, const std::string& a3, int32_t maxMsgLen)
		: field_0(0)
		, field_4(maxMsgLen)
		, field_8(a3)
		, field_C(a2) {
		if(a2.size()) {
			this->field_10 = '<' + a2 + "> " + a3;
		} else {
			this->field_10 = a3;
		}
	}
	GuiMessage& operator=(const GuiMessage& a2) = default;
	GuiMessage& operator=(GuiMessage&& a2) {
		this->field_0 = a2.field_0;
		this->field_4 = a2.field_4;
		this->field_8 = a2.field_8;
		this->field_C = a2.field_C;
		this->field_10 = a2.field_10;
		return *this;
	}
	~GuiMessage(){}
};
