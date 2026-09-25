#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct ContainerAckPacket : Packet{
	int16_t field_C;
	uint8_t field_E;
	bool field_F;
	ContainerAckPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_CONTAINER_ACK_PACKET);
		stream->Write<uint8_t>(this->field_E);
		stream->Write<int16_t>(this->field_C);
		stream->Write<bool>(this->field_F);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<uint8_t>(this->field_E);
		stream->Read<int16_t>(this->field_C);
		stream->Read<bool>(this->field_F);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
