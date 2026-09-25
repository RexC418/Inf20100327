#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct SetEntityLinkPacket : Packet{
	int32_t typeMaybe, rider, riding;

	SetEntityLinkPacket(int32_t type, int32_t rider, int32_t riding) {
		this->typeMaybe = type;
		this->rider = rider;
		this->riding = riding;
	}
	SetEntityLinkPacket() {
	}

	virtual ~SetEntityLinkPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_SET_ENTITY_LINK_PACKET);
		stream->Write<int32_t>(this->rider);
		stream->Write<int32_t>(this->riding);
		stream->Write<int32_t>(this->typeMaybe);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->rider);
		stream->Read<int32_t>(this->riding);
		stream->Read<int32_t>(this->typeMaybe);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
