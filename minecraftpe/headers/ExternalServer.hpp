#pragma once
#include <_types.h>
#include <string>

struct ExternalServer
{
	int32_t field_0;
	std::string field_4, field_8;
	int32_t field_C;

	ExternalServer() {
	}
	ExternalServer(const ExternalServer& a2) {
		this->field_0 = a2.field_0;
		this->field_4 = a2.field_4;
		this->field_8 = a2.field_8;
		this->field_C = a2.field_C;
	}
	ExternalServer(int32_t a2, const std::string& a3, const std::string& a4, int32_t a5) {
		this->field_0 = a2;
		this->field_4 = a3;
		this->field_8 = a4;
		this->field_C = a5;
	}
	//~ExternalServer();
};
