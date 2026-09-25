#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>
#include <cstdint>

struct StartGamePacket : Packet{
	int64_t seed;
	int32_t genver, gamemode, eid;
	float x, y, z;
	StartGamePacket() {
	}
	StartGamePacket(int64_t seed, int genver, int gm, int eid, float x, float y, float z) {
		this->seed = seed;
		this->genver = genver;
		this->gamemode = gm;
		this->eid = eid;
		this->x = x;
		this->y = y;
		this->z = z;
	}
	virtual ~StartGamePacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_START_GAME_PACKET);
		stream->Write<int64_t>(this->seed);
		stream->Write<int32_t>(this->genver);
		stream->Write<int32_t>(this->gamemode);
		stream->Write<int32_t>(this->eid);
		stream->Write<float>(this->x);
		stream->Write<float>(this->y);
		stream->Write<float>(this->z);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int64_t>(this->seed);
		stream->Read<int32_t>(this->genver);
		stream->Read<int32_t>(this->gamemode);
		stream->Read<int32_t>(this->eid);
		stream->Read<float>(this->x);
		stream->Read<float>(this->y);
		stream->Read<float>(this->z);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
