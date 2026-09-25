#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct RequestChunkPacket : Packet{
	int32_t x, z;
	RequestChunkPacket() {
	}
	RequestChunkPacket(int32_t x, int32_t z) {
		this->x = x;
		this->z = z;
	}

	virtual ~RequestChunkPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_REQUEST_CHUNK_PACKET);
		stream->Write<int32_t>(this->x);
		stream->Write<int32_t>(this->z);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->x);
		stream->Read<int32_t>(this->z);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
