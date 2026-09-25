#pragma once
#include <network/Packet.hpp>
#include <entity/Player.hpp>
#include <network/NetEventCallback.hpp>

struct Player;
struct RespawnPacket : Packet{
	float x, y, z;
	int32_t eid;
	RespawnPacket() {
	}
	RespawnPacket(Player* p) {
		this->x = p->posX;
		this->y = p->posY;
		this->z = p->posZ;
		this->eid = p->entityId;
	}

	virtual ~RespawnPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_RESPAWN_PACKET);
		stream->Write<int32_t>(this->eid);
		stream->Write<float>(this->x);
		stream->Write<float>(this->y);
		stream->Write<float>(this->z);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->eid);
		stream->Read<float>(this->x);
		stream->Read<float>(this->y);
		stream->Read<float>(this->z);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
