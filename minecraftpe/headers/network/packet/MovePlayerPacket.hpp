#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct MovePlayerPacket : Packet{
	int32_t eid;
	float x, y, z;
	float pitch, yaw, bodyYaw;
	MovePlayerPacket() {
	}
	MovePlayerPacket(int32_t eid, float x, float y, float z, float p, float yaw, float byaw) {
		this->eid = eid;
		this->x = x;
		this->y = y;
		this->z = z;
		this->pitch = p;
		this->yaw = yaw;
		this->bodyYaw = byaw;
	}

	virtual ~MovePlayerPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_MOVE_PLAYER_PACKET);
		stream->Write<int32_t>(this->eid);
		stream->Write<float>(this->x);
		stream->Write<float>(this->y);
		stream->Write<float>(this->z);
		stream->Write<float>(this->yaw);
		stream->Write<float>(this->pitch);
		stream->Write<float>(this->bodyYaw);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->eid);
		stream->Read<float>(this->x);
		stream->Read<float>(this->y);
		stream->Read<float>(this->z);
		stream->Read<float>(this->yaw);
		stream->Read<float>(this->pitch);
		stream->Read<float>(this->bodyYaw);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
