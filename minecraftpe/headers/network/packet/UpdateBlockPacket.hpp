#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct UpdateBlockPacket : Packet{
	int32_t x, z;
	uint8_t y;
	uint8_t id, meta;
	UpdateBlockPacket() {
	}
	UpdateBlockPacket(int32_t x, int32_t y, int32_t z, int32_t id, int32_t meta) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->id = id;
		this->meta = meta;
	}

	virtual ~UpdateBlockPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_UPDATE_BLOCK_PACKET);
		stream->Write<int32_t>(this->x);
		stream->Write<int32_t>(this->z);
		stream->Write<uint8_t>(this->y);
		stream->Write<uint8_t>(this->id);
		stream->Write<uint8_t>(this->meta);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->x);
		stream->Read<int32_t>(this->z);
		stream->Read<uint8_t>(this->y);
		stream->Read<uint8_t>(this->id);
		stream->Read<uint8_t>(this->meta);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
