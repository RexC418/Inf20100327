#pragma once
#include <_types.h>

struct Material{
	bool_t flammable = 0;
	bool_t translucent = 0;
	bool_t alwaysDestroyable = 0;
	bool_t replaceable = 0;

	static Material* air, *dirt, *wood, *stone;
	static Material* metal, *water, *lava, *leaves;
	static Material* plant, *replaceable_plant, *sponge;
	static Material* cloth, *fire, *sand, *decoration;
	static Material* glass, *explosive, *coral, *ice;
	static Material* topSnow, *snow, *cactus, *clay;
	static Material* vegetable, *portal, *cake, *web;

	static void initMaterials(void);
	static void teardownMaterials(void);

	virtual bool_t isLiquid(void) const{
		return 0;
	}
	virtual bool_t letsWaterThrough(void) const{
		if(this->isLiquid()) return 0;
		return !this->isSolid();
	}
	virtual bool_t isSolid(void) const{
		return 1;
	}
	virtual bool_t blocksLight(void) const{
		return 1;
	}
	virtual bool_t isSolidBlocking(void) const{
		if(this->translucent) return 0;
		return this->blocksMotion();
	}
	virtual bool_t isAlwaysDestroyable(void) const {
		return this->alwaysDestroyable;
	}
	virtual bool_t blocksMotion(void) const{
		return 1;
	}
	virtual bool_t isFlammable(void) const{
		return this->flammable;
	}
	virtual bool_t isReplaceable(void) const{
		return this->replaceable;
	}

	virtual ~Material(){}

	Material(void){
		this->alwaysDestroyable = 1;
		this->flammable = this->translucent = this->replaceable = 0;
	}
};
