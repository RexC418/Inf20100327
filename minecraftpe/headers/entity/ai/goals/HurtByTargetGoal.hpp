#pragma once
#include <entity/ai/goals/TargetGoal.hpp>
#include <entity/Mob.hpp>

struct HurtByTargetGoal: TargetGoal
{
	HurtByTargetGoal(Mob* mob, float radius)
		: TargetGoal(mob, radius, 0) {
		this->field_D = 0;
		this->setRequiredControlFlags(1);
	}

	virtual ~HurtByTargetGoal(){}
	virtual bool_t canUse() {
		return this->canAttack(this->mob->getLastHurtByMob(), 1);
	}
	virtual void start() {
		mob->setTarget(mob->getLastHurtByMob());
	}
};
