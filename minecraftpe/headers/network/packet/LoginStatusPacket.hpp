#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct LoginStatusPacket : Packet{
	int32_t status;
	LoginStatusPacket() {
	}
	LoginStatusPacket(int32_t status) {
		this->status = status;
	}

	virtual ~LoginStatusPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_LOGIN_STATUS_PACKET);
		stream->Write<int32_t>(this->status);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->status);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
