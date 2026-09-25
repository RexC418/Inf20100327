#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct ContainerSetDataPacket : Packet{
	int16_t field_C, field_E;
	uint8_t field_10, field_11, field_12, field_13;
	ContainerSetDataPacket() {
	}
	ContainerSetDataPacket(int16_t c, int16_t e, uint8_t f10) {
		this->field_C = c;
		this->field_E = e;
		this->field_10 = f10;
	}
	virtual ~ContainerSetDataPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_CONTAINER_SET_DATA_PACKET);
		stream->Write<uint8_t>(this->field_10);
		stream->Write<int16_t>(this->field_C);
		stream->Write<int16_t>(this->field_E);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<uint8_t>(this->field_10);
		stream->Read<int16_t>(this->field_C);
		stream->Read<int16_t>(this->field_E);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
