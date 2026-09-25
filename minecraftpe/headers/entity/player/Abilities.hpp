#pragma once
#include <_types.h>
#include <nbt/CompoundTag.hpp>
struct Abilities
{
	bool_t invulnerable;
	bool_t flying;
	bool_t mayfly;
	bool_t instabuild;

	void addSaveData(CompoundTag* a2) {
		CompoundTag* v4 = new CompoundTag();
		v4->putBoolean("invulnerable", this->invulnerable);
		v4->putBoolean("flying", this->flying);
		v4->putBoolean("mayfly", this->mayfly);
		v4->putBoolean("instabuild", this->instabuild);
		a2->put("abilities", v4);
	}
	void loadSaveData(CompoundTag* a2) {
		if(a2->contains("abilities")) {
			CompoundTag* v5 = a2->getCompound("abilities"); //inlined
			this->invulnerable = v5->getByte("invulnerable") != 0;
			this->flying = v5->getByte("flying") != 0;
			this->mayfly = v5->getByte("mayfly") != 0;
			this->instabuild = v5->getByte("instabuild") != 0;
		}
	}
};
