#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct HurtArmorPacket : Packet{
	int8_t health;
	char align1, align2, align3;

	HurtArmorPacket(int8_t h) {
		this->health = h;
	}
	HurtArmorPacket() {
	}
	virtual ~HurtArmorPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_HURT_ARMOR_PACKET);
		stream->Write<int8_t>(this->health);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int8_t>(this->health);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
