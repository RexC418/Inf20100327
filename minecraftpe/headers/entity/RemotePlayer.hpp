#pragma once
#include <entity/Player.hpp>

struct RemotePlayer: Player
{
	bool_t _usingItem;
	int8_t field_D55, field_D56, field_D57;

	RemotePlayer(Level* a2, bool_t a3);

	virtual ~RemotePlayer() {
	}
	virtual void tick();
	virtual void aiStep();
};
