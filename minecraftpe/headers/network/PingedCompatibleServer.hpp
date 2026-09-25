#pragma once
#include <_types.h>
#include <RakString.h>

struct PingedCompatibleServer
{
	RakNet::RakString field_0;
	RakNet::SystemAddress field_4;
	int32_t field_18;
	int8_t field_1C, field_1D, field_1E, field_1F;
	PingedCompatibleServer(){}
	PingedCompatibleServer(const PingedCompatibleServer& a2) {
		this->field_0 = a2.field_0;
		this->field_4 = a2.field_4;
		this->field_18 = a2.field_18;
		this->field_1C = a2.field_1C;
	}
	PingedCompatibleServer& operator=(const PingedCompatibleServer& a2) {
		this->field_0 = a2.field_0;
		this->field_4 = a2.field_4;
		this->field_18 = a2.field_18;
		this->field_1C = a2.field_1C;

		return *this;
	}
};
