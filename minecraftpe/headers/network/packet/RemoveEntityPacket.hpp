#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct RemoveEntityPacket : Packet{
	int32_t eid;
	RemoveEntityPacket(int32_t eid) {
		this->eid = eid;
	}
	RemoveEntityPacket() {
	}
	virtual ~RemoveEntityPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_REMOVE_ENTITY_PACKET);
		stream->Write<int32_t>(this->eid);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->eid);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
