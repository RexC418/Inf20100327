#pragma once
#include <entity/Entity.hpp>

struct Arrow : Entity{
	static const float ARROW_BASE_DAMAGE;
	int32_t shake;
	int32_t shooterEID;
	bool_t critical;
	int8_t field_125, field_126, field_127;
	int32_t xTile, yTile, zTile;
	int32_t inTile, inData;
	bool_t inGround;
	int8_t field_13D, field_13E, field_13F;
	int32_t ticksInGround;
	int32_t ticksInAir;

	Arrow(Level*);
	Arrow(Level*, Mob*, Mob*, float, float);
	Arrow(Level*, Mob*, float);
	Arrow(Level*, float, float, float);
	void _init();
	void shoot(float, float, float, float, float);

	virtual ~Arrow() {
	}
	virtual void lerpMotion(float, float, float);
	virtual void tick();
	virtual float getShadowRadius() {
		if(this->inGround) return 0;
		else return 0.1;
	}
	virtual float getShadowHeightOffs();
	virtual void playerTouch(Player*);
	virtual int32_t getEntityTypeId() const;
	virtual int32_t getAuxData();
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
};
