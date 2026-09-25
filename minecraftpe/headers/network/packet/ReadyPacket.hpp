#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct ReadyPacket : Packet{
	char status;
	int8_t align1, align2, align3;

	ReadyPacket(int8_t s) {
		this->status = s;
	}

	virtual ~ReadyPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_READY_PACKET);
		stream->Write<char>(this->status);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<char>(this->status);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
