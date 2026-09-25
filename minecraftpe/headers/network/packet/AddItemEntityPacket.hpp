#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <entity/ItemEntity.hpp>
#include <network/NetEventCallback.hpp>

struct ItemEntity;
struct AddItemEntityPacket : Packet{
	int32_t eid;
	float x, y, z;
	int16_t itemID;
	int16_t itemMeta;
	int8_t count;
	int8_t motionX, motionY, motionZ;
	AddItemEntityPacket(ItemEntity* a2) {
		this->eid = a2->entityId;
		this->x = a2->posX;
		this->y = a2->posY;
		this->z = a2->posZ;
		this->itemID = a2->itemInstance.getId();
		this->itemMeta = a2->itemInstance.getAuxValue();
		this->count = a2->itemInstance.count;
		this->motionX = (int)(a2->motionX * 128.0);
		this->motionY = (int)(a2->motionY * 128.0);
		this->motionZ = (int)(a2->motionZ * 128.0);
		a2->motionX = (float)this->motionX * 0.0078125;
		a2->motionY = (float)this->motionY * 0.0078125;
		a2->motionZ = (float)this->motionZ * 0.0078125;
	}
	AddItemEntityPacket() {
	}
	virtual ~AddItemEntityPacket() {
	}
	virtual void write(RakNet::BitStream* stream){
		stream->Write<uint8_t>(PID_ADD_ITEM_ENTITY_PACKET);
		stream->Write<int32_t>(this->eid);
		stream->Write<int16_t>(this->itemID);
		stream->Write<int8_t>(this->count);
		stream->Write<int16_t>(this->itemMeta);
		stream->Write<float>(this->x);
		stream->Write<float>(this->y);
		stream->Write<float>(this->z);
		stream->Write<int8_t>(this->motionX);
		stream->Write<int8_t>(this->motionY);
		stream->Write<int8_t>(this->motionZ);
	}
	virtual void read(RakNet::BitStream* stream){
		stream->Read<int32_t>(this->eid);
		stream->Read<int16_t>(this->itemID);
		stream->Read<int8_t>(this->count);
		stream->Read<int16_t>(this->itemMeta);
		stream->Read<float>(this->x);
		stream->Read<float>(this->y);
		stream->Read<float>(this->z);
		stream->Read<int8_t>(this->motionX);
		stream->Read<int8_t>(this->motionY);
		stream->Read<int8_t>(this->motionZ);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3){
		a3->handle(a2, this);
	}
};
