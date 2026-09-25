#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct EntityEventPacket : Packet{
	int32_t eid;
	uint8_t event;
	char align1, align2, align3;
	EntityEventPacket() {
	}
	EntityEventPacket(int32_t eid, uint8_t event) {
		this->eid = eid;
		this->event = event;
	}

	virtual ~EntityEventPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_ENTITY_EVENT_PACKET);
		stream->Write<int32_t>(this->eid);
		stream->Write<uint8_t>(this->event);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->eid);
		stream->Read<uint8_t>(this->event);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
