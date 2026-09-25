#pragma once
#include <network/packet/MoveEntityPacket.hpp>
#include <entity/Entity.hpp>

struct MoveEntityPacket_PosRot : MoveEntityPacket{
	MoveEntityPacket_PosRot() :
			MoveEntityPacket(1) {
	}
	MoveEntityPacket_PosRot(Entity* e) {
		this->pitch = e->pitch;
		this->eid = e->entityId;
		this->yaw = e->yaw;
		this->posY = e->posY - e->ridingHeight;
		this->posX = e->posX;
		this->posZ = e->posZ;
	}

	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_MOVE_ENTITY_POSROT_PACKET);
		stream->Write<int32_t>(this->eid);
		stream->Write<float>(this->posX);
		stream->Write<float>(this->posY);
		stream->Write<float>(this->posZ);
		stream->Write<float>(this->yaw);
		stream->Write<float>(this->pitch);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->eid);
		stream->Read<float>(this->posX);
		stream->Read<float>(this->posY);
		stream->Read<float>(this->posZ);
		stream->Read<float>(this->yaw);
		stream->Read<float>(this->pitch);
	}
};
