#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct PlaceBlockPacket : Packet{
	int32_t field_C;
	int32_t field_10;
	int32_t field_14;
	uint8_t field_18;
	uint8_t field_19;
	uint8_t field_1A;
	uint8_t field_1B;

	PlaceBlockPacket() {
	}

	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_PLACE_BLOCK_PACKET);
		stream->Write<int32_t>(this->field_C);
		stream->Write<int32_t>(this->field_10);
		stream->Write<int32_t>(this->field_14);
		stream->Write<uint8_t>(this->field_18);
		stream->Write<uint8_t>(this->field_19);
		stream->Write<uint8_t>(this->field_1A);
		stream->Write<uint8_t>(this->field_1B);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->field_C);
		stream->Read<int32_t>(this->field_10);
		stream->Read<int32_t>(this->field_14);
		stream->Read<uint8_t>(this->field_18);
		stream->Read<uint8_t>(this->field_19);
		stream->Read<uint8_t>(this->field_1A);
		stream->Read<uint8_t>(this->field_1B);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
