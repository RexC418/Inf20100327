#pragma once
#include <network/Packet.hpp>
#include <entity/Entity.hpp>
#include <network/NetEventCallback.hpp>
struct Entity;
struct RotateHeadPacket : Packet{
	int32_t eid;
	int8_t headYaw;
	int8_t field_11, field_12, field_13;
	RotateHeadPacket(Entity* e, float yaw) {
		this->eid = e->entityId;
		this->headYaw = yaw;
	}
	RotateHeadPacket() {
	}

	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_ROTATE_HEAD_PACKET);
		stream->Write<int32_t>(this->eid);
		stream->Write<int8_t>(this->headYaw);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->eid);
		stream->Read<int8_t>(this->headYaw);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
