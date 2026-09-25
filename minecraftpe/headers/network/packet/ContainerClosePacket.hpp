#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct ContainerClosePacket : Packet{
UNK	uint8_t field_C;
	char align1, align2, align3;
	ContainerClosePacket() {
	}
	ContainerClosePacket(uint8_t field_C) {
		this->field_C = field_C;
	}
	virtual ~ContainerClosePacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_CONTAINER_CLOSE_PACKET);
		stream->Write<uint8_t>(this->field_C);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<uint8_t>(this->field_C);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
