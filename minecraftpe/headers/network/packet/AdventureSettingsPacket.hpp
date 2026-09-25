#pragma once
#include <_types.h>
#include <network/Packet.hpp>
#include <network/NetEventCallback.hpp>

struct AdventureSettingsPacket: Packet
{
	enum Flags {
		AS_ALLOW_INTERACT = 0x1,
		AS_ENABLE_PVP = 0x2,
		AS_ENABLE_PVE = 0x4,
		AS_FIELD_3 = 0x8,
		AS_NO_DAYLIGHT_CYCLE = 0x10,
		AS_FIELD_5 = 0x20
	};

	int32_t flags;

	AdventureSettingsPacket() {
	}
	void set(AdventureSettingsPacket::Flags a2, bool_t a3) {
		this->flags = a3 ? (this->flags | a2) : (this->flags & ~a2);
	}

	virtual ~AdventureSettingsPacket(){}
	virtual void write(RakNet::BitStream* stream) {
		stream->Write<uint8_t>(PID_ADVENTURE_SETTINGS_PACKET);
		stream->Write<int32_t>(this->flags);

	}
	virtual void read(RakNet::BitStream* stream) {
		stream->Read<int32_t>(this->flags);
	}
	virtual void handle(const RakNet::RakNetGUID& a2, NetEventCallback* a3) {
		a3->handle(a2, this);
	}
};
