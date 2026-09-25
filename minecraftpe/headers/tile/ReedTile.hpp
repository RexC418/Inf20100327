#pragma once
#include <tile/Tile.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>

struct ReedTile : Tile{

	ReedTile(int32_t id, const std::string& name, Material* mat) :
			Tile(id, name, mat) {
		this->setShape(0.125, 0.0, 0.125, 0.875, 1.0, 0.875);
		this->setTicking(1);
	}

	virtual ~ReedTile() {
	}
	virtual bool_t onFertilized(Level* level, int32_t x, int32_t y, int32_t z) {
		int32_t v5; // r5
		int32_t v6; // r4
		int32_t v11; // r5
		int32_t v12; // r11
		v5 = y - 1;
		v6 = y + 1;
		while (v5 > 0 && level->getTile(x, v5, z) == this->blockID) {
			--v5;
		}
		while (v6 <= 127 && level->getTile(x, v6, z) == this->blockID) {
			++v6;
		}
		v11 = v5 - (v6 - 1) + 3;
		if (v11 <= 0) {
			return 0;
		}
		v12 = v6 - 1 + v11;
		while (v6 <= v12) {
			level->setTileAndData(x, v6++, z, this->blockID, 0, 3);
		}
		return 1;
	}
	virtual bool_t isCubeShaped() {
		return 0;
	}
	virtual int32_t getRenderShape() {
		return 1;
	}
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t) {
		return 0;
	}
	virtual bool_t isSolidRender() {
		return 0;
	}
	virtual bool_t mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
		int32_t v5; // r6
		int32_t v9; // r0
		v5 = y - 1;
		v9 = level->getTile(x, y - 1, z);
		if (v9 == this->blockID) {
			return 1;
		}
		if (v9 != Tile::grass->blockID && v9 != Tile::dirt->blockID && v9 != Tile::sand->blockID) {
			return 0;
		}
		if (Material::water == level->getMaterial(x - 1, v5, z) || Material::water == level->getMaterial(x + 1, v5, z) || Material::water == level->getMaterial(x, v5, z - 1)) {
			return 1;
		}
		return Material::water == level->getMaterial(x, v5, z + 1);
	}
	virtual void tick(Level* level, int32_t x, int32_t y, int32_t z, Random* random) {
		int32_t v6; // r9
		int32_t i; // r8
		int32_t v13; // r0
		int32_t za; // [sp+28h] [bp+0h]
		v6 = y + 1;
		if (level->isEmptyTile(x, y + 1, z)) {
			for (i = 1; level->getTile(x, y - i, z) == this->blockID; ++i) {
				;
			}
			if (i <= 2) {
				v13 = level->getData(x, y, z);
				if (v13 == 15) {
					level->setTile(x, v6, z, this->blockID, 3);
					za = 0;
				} else {
					za = v13 + 1;
				}
				level->setData(x, y, z, za, 4);
			}
		}
	}
	virtual void neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t, int32_t, int32_t, int32_t) {
		if (!this->canSurvive(level, x, y, z)) {
			this->popResource(level, x, y, z, ItemInstance(Item::reeds));
			level->setTile(x, y, z, 0, 3);
		}
	}
	virtual int32_t getResource(int32_t, Random*) {
		return Item::reeds->itemID;
	}
	virtual int32_t getRenderLayer() {
		if (this->goodGraphics) return 3;

		return 1;
	}
	virtual bool_t canSurvive(Level* level, int32_t x, int32_t y, int32_t z) {
		return this->mayPlace(level, x, y, z);
	}
};
