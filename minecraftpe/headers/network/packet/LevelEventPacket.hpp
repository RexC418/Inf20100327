#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>


struct LevelEventPacket : Packet{
	int16_t evid;
	int16_t x, y, z;
	int32_t data;
	LevelEventPacket() {
	}
	LevelEventPacket(int16_t evid, int16_t x, int16_t y, int16_t z, int32_t data) {
		this->evid = evid;
		this->x = x;
		this->y = y;
		this->z = z;
		this->data = data;
	}
	virtual ~LevelEventPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_LEVEL_EVENT_PACKET);
		stream->Write<int16_t>(this->evid);
		stream->Write<int16_t>(this->x);
		stream->Write<int16_t>(this->y);
		stream->Write<int16_t>(this->z);
		stream->Write<int32_t>(this->data);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int16_t>(this->evid);
		stream->Read<int16_t>(this->x);
		stream->Read<int16_t>(this->y);
		stream->Read<int16_t>(this->z);
		stream->Read<int32_t>(this->data);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
