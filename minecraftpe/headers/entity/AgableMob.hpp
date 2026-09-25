#pragma once
#include <entity/PathfinderMob.hpp>

struct AgableMob: PathfinderMob
{
	int32_t age;

	AgableMob(Level*);

	int32_t getAge();
	void setAge(int32_t);

	virtual ~AgableMob() {
	}
	virtual float getShadowRadius() {
		float v3 = this->entityWidth * 0.8;
		float v4 = 0.5;
		if(!this->isBaby()) {
			v4 = 1.0;
		}
		return v3 * v4;
	}
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual void aiStep();
	virtual bool_t isBaby();
};
