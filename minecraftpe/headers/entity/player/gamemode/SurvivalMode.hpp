#pragma once
#include <entity/player/gamemode/GameMode.hpp>

struct SurvivalMode: GameMode
{
	int32_t xCurrent, yCurrent, zCurrent;

	SurvivalMode(Minecraft*);

	virtual ~SurvivalMode() {
	}

	virtual void startDestroyBlock(int32_t, int32_t, int32_t, int32_t);
	virtual bool_t destroyBlock(int32_t, int32_t, int32_t, int32_t);
	virtual void continueDestroyBlock(int32_t, int32_t, int32_t, int32_t);
	virtual void stopDestroyBlock();
	virtual bool_t canHurtPlayer() {
		return 1;
	}
	virtual bool_t isSurvivalType() {
		return 1;
	}
	virtual void initAbilities(Abilities&);
};
