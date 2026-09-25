#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct SetHealthPacket : Packet{
	int32_t health;
	SetHealthPacket() {
	}
	SetHealthPacket(int32_t h) {
		this->health = h;
	}

	virtual ~SetHealthPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_SET_HEALTH_PACKET);
		int8_t a = (int8_t) ((this->health));
		stream->Write<int8_t>(a);
	}
	virtual void read(RakNet::BitStream* stream) {
		int8_t a;
		stream->Read<int8_t>(a);
		this->health = a;
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
