#pragma once
#include <network/Packet.hpp>
#include <entity/Player.hpp>
#include <network/NetEventCallback.hpp>

static void _D6602FA2_armorId(int8_t* res, ItemInstance* it) {
	if (it) {
		*res = it->getId();
	} else {
		*res = -1;
	}
}
struct PlayerArmorEquipmentPacket : Packet{
	int32_t eid;
	int8_t headId, chestId, legsId, bootsId;

	PlayerArmorEquipmentPacket(struct Player* a2) {
		this->eid = a2->entityId;
		_D6602FA2_armorId(&this->headId, a2->getArmor(0));
		_D6602FA2_armorId(&this->chestId, a2->getArmor(1));
		_D6602FA2_armorId(&this->legsId, a2->getArmor(2));
		_D6602FA2_armorId(&this->bootsId, a2->getArmor(3));
	}
	PlayerArmorEquipmentPacket() {
	}
	virtual ~PlayerArmorEquipmentPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_PLAYER_ARMOR_EQUIPMENT_PACKET);
		stream->Write<int32_t>(this->eid);
		stream->Write<int8_t>(this->headId);
		stream->Write<int8_t>(this->chestId);
		stream->Write<int8_t>(this->legsId);
		stream->Write<int8_t>(this->bootsId);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->eid);
		stream->Read<int8_t>(this->headId);
		stream->Read<int8_t>(this->chestId);
		stream->Read<int8_t>(this->legsId);
		stream->Read<int8_t>(this->bootsId);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
