#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct SetTimePacket : Packet{
	int32_t timeValue;
	bool stopTime;
	char align, align1, align2;
	SetTimePacket() {
	}
	SetTimePacket(int32_t tv, bool_t stopTime) {
		this->timeValue = tv;
		this->stopTime = stopTime;
	}

	virtual ~SetTimePacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_SET_TIME_PACKET);
		stream->Write<int32_t>(this->timeValue);
		stream->Write<bool>(this->stopTime);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->timeValue);
		stream->Read<bool>(this->stopTime);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
