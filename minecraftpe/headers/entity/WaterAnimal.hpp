#pragma once
#include <entity/PathfinderMob.hpp>

struct WaterAnimal: PathfinderMob
{
	WaterAnimal(Level*);
	int32_t getExperienceReward(Player*); //release feature leaks :scream:

	virtual ~WaterAnimal(){}
	virtual int32_t getCreatureBaseType() const;
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual bool_t isWaterMob();
	virtual int32_t getAmbientSoundInterval();
	virtual float getBaseSpeed(){
		return 0.2;
	}
	virtual bool_t canSpawn();
	virtual bool_t removeWhenFarAway();
};
