#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct MoveEntityPacket : Packet{
	int32_t eid;
	float posX, posY, posZ;
	float pitch, yaw;
	bool_t hasrot;
	MoveEntityPacket() {
	}
	MoveEntityPacket(bool hasrot) {
		this->hasrot = hasrot;
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_MOVE_ENTITY_PACKET);
	}
	virtual void read(RakNet::BitStream* stream) {
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
