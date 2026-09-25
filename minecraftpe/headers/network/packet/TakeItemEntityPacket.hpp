#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct TakeItemEntityPacket : Packet{
	int32_t target, eid;

	TakeItemEntityPacket(int32_t eid, int32_t targt) {
		this->eid = eid;
		this->target = targt;
	}
	TakeItemEntityPacket() {
	}
	virtual ~TakeItemEntityPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_TAKE_ITEM_ENTITY_PACKET);
		stream->Write<int32_t>(this->target);
		stream->Write<int32_t>(this->eid);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->target);
		stream->Read<int32_t>(this->eid);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
