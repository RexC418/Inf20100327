#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct RemoveBlockPacket : Packet{
	int32_t eid;
	int32_t x, z;
	uint8_t y;
	int8_t field_19, field_1A, field_1B;
	RemoveBlockPacket() {
	}
	RemoveBlockPacket(int32_t eid, int32_t x, int32_t y, int32_t z) {
		this->eid = eid;
		this->x = x;
		this->z = z;
		this->y = y;
	}
	virtual ~RemoveBlockPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_REMOVE_BLOCK_PACKET);
		stream->Write<int32_t>(this->eid);
		stream->Write<int32_t>(this->x);
		stream->Write<int32_t>(this->z);
		stream->Write<uint8_t>(this->y);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->eid);
		stream->Read<int32_t>(this->x);
		stream->Read<int32_t>(this->z);
		stream->Read<uint8_t>(this->y);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
