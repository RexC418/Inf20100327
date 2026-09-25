#pragma once
#include <_types.h>

struct Mob;

struct MoveControl
{
	static const float MIN_SPEED;
	static const float MIN_SPEED_SQR;
	static const float MAX_TURN;
	Mob* controlledEntity;
	float posX, posY, posZ;
	float speedMultiplier;
	bool_t _hasWanted;
	char align[3];

	MoveControl(Mob*);
	float getSpeed();
	bool_t hasWanted();
	void setWantedPosition(float x, float y, float z, float speed);

	virtual ~MoveControl(){}
	virtual void tick();
};
