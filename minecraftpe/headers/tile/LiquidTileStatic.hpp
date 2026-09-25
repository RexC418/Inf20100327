#pragma once
#include <tile/LiquidTile.hpp>

struct LiquidTileStatic: LiquidTile
{
	LiquidTileStatic(int32_t a2, const struct Material* a3, const std::string& a4, const std::string& a5) :
			LiquidTile(a2, a3, a4, a5) {
		this->setTicking(0);
		if (a3 == Material::lava) this->setTicking(1);
	}
	void setDynamic(Level* level, int32_t x, int32_t y, int32_t z) {
		int32_t data; // r0
		int32_t id; // r10
		int32_t v12; // r0
		data = level->getData(x, y, z);
		level->setTileAndDataNoUpdate(x, y, z, this->blockID - 1, data);
		level->setTilesDirty(x, y, z, x, y, z);
		id = this->blockID - 1;
		v12 = this->getTickDelay();
		level->addToTickNextTick(x, y, z, id, v12);
	}

	virtual ~LiquidTileStatic() {
	}
	virtual void tick(Level* level, int32_t x, int32_t y, int32_t z, Random* random) {
		if (this->material == Material::lava) {
			this->_trySpreadFire(level, x, y, z, random);
		}
	}
	virtual void neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t, int32_t, int32_t, int32_t) {
		this->updateLiquid(level, x, y, z);
		if (level->getTile(x, y, z) == this->blockID) {
			this->setDynamic(level, x, y, z);
		}
	}

};
