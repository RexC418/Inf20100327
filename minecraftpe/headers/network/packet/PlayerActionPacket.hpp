#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct PlayerActionPacket : Packet{
	int32_t x, y, z;
	int32_t face, action, eid;
	PlayerActionPacket() :
			PlayerActionPacket(0, 0, 0, 0, 0, 0) {
	}
	PlayerActionPacket(int32_t eid, int32_t x, int32_t y, int32_t z, int32_t face, int32_t action) {
		this->eid = eid;
		this->x = x;
		this->y = y;
		this->z = z;
		this->face = face;
		this->action = action;
	}

	virtual ~PlayerActionPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_PLAYER_ACTION_PACKET);
		stream->Write<int32_t>(this->action);
		stream->Write<int32_t>(this->x);
		stream->Write<int32_t>(this->y);
		stream->Write<int32_t>(this->z);
		stream->Write<int32_t>(this->face);
		stream->Write<int32_t>(this->eid);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->action);
		stream->Read<int32_t>(this->x);
		stream->Read<int32_t>(this->y);
		stream->Read<int32_t>(this->z);
		stream->Read<int32_t>(this->face);
		stream->Read<int32_t>(this->eid);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
