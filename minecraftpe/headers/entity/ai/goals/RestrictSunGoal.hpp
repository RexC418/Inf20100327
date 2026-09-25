#pragma once
#include <entity/ai/Goal.hpp>

struct PathfinderMob;
struct RestrictSunGoal: Goal
{
	PathfinderMob* holder;

	RestrictSunGoal(PathfinderMob* a2);

	virtual ~RestrictSunGoal() {
	}
	virtual bool_t canUse();
	virtual void start();
	virtual void stop();
};
