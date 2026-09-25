#pragma once
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct PlayerInputPacket : Packet{
	float moveForward, moveStrafe;
	bool isJumping, isSneaking;
	char align, align1;
	PlayerInputPacket() {
	}
	PlayerInputPacket(float fwd, float stf, bool jmp, bool snk) {
		this->moveForward = fwd;
		this->moveStrafe = stf;
		this->isJumping = jmp;
		this->isSneaking = snk;
	}

	virtual ~PlayerInputPacket() {
	}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_PLAYER_INPUT_PACKET);
		stream->Write<float>(this->moveStrafe);
		stream->Write<float>(this->moveForward);
		stream->Write<bool>(this->isJumping);
		stream->Write<bool>(this->isSneaking);
	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<float>(this->moveStrafe);
		stream->Read<float>(this->moveForward);
		stream->Read<bool>(this->isJumping);
		stream->Read<bool>(this->isSneaking);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
