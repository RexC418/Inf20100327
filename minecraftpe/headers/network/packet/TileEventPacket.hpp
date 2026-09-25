#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct TileEventPacket : Packet{
	int32_t x, y, z;
	int32_t case1, case2;
	TileEventPacket() {
	}
	TileEventPacket(int x, int y, int z, int c1, int c2) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->case1 = c1;
		this->case2 = c2;
	}
	virtual ~TileEventPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_TILE_EVENT_PACKET);
		stream->Write<int32_t>(this->x);
		stream->Write<int32_t>(this->y);
		stream->Write<int32_t>(this->z);
		stream->Write<int32_t>(this->case1);
		stream->Write<int32_t>(this->case2);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->x);
		stream->Read<int32_t>(this->y);
		stream->Read<int32_t>(this->z);
		stream->Read<int32_t>(this->case1);
		stream->Read<int32_t>(this->case2);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
