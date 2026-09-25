#pragma once
#include <entity/Mob.hpp>
#include <level/Level.hpp>

struct CameraEntity: Mob
{
	int32_t followEid;

	CameraEntity(Level* a2) :
			Mob(a2) {
		this->followEid = -1;
		this->moveTo(128.0, 72.0, 128.0, 0.0, 90.0);
	}
	virtual ~CameraEntity() {
	}
	virtual void tick() {
		if (this->followEid >= 0) {
			this->prevPosX = this->prevX = this->posX;
			this->prevPosY = this->prevY = this->posY;
			this->prevPosZ = this->prevZ = this->posZ;
			this->prevPitch = this->pitch;
			this->prevYaw = this->yaw;
			Entity* e = this->level->getEntity(this->followEid);
			if (e) {
				this->setPos(e->posX, e->posY + 6.0, e->posZ);
			}
		}
	}
	virtual int32_t getEntityTypeId() const {
		return 0;
	}
	virtual float getBaseSpeed() {
		return 0.2;
	}
};
