#pragma once
#include <tile/EntityTile.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>

struct SignTile : EntityTile{
	bool_t field_80;
	char field_81, field_82, field_83;

	SignTile(int32_t id, bool_t a3) :
			EntityTile(id, Material::wood) {
		this->field_80 = a3;
		this->textureUV = this->getTextureUVCoordinateSet("planks", 0);
		this->setShape(0.25, 0.0, 0.25, 0.75, 1.0, 0.75);
	}

	virtual ~SignTile() {
	}
	virtual bool_t isCubeShaped() {
		return 0;
	}
	virtual int32_t getRenderShape() {
		return -1;
	}
	virtual void updateShape(LevelSource* level, int32_t x, int32_t y, int32_t z) {
		int32_t v6;
		if (!this->field_80) {
			v6 = level->getData(x, y, z);
			this->setShape(0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
			switch (v6) {
			case 2:
				this->setShape(0.0, 0.28125, 0.875, 1.0, 0.78125, 1.0);
				break;
			case 3:
				this->setShape(0.0, 0.28125, 0.0, 1.0, 0.78125, 0.125);
				break;
			case 4:
				this->setShape(0.875, 0.28125, 0.0, 1.0, 0.78125, 1.0);
				break;
			case 5:
				this->setShape(0.0, 0.28125, 0.0, 0.125, 0.78125, 1.0);
				break;
			}
		}
	}
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t) {
		return 0;
	}
	virtual AABB getTileAABB(Level* level, int32_t x, int32_t y, int32_t z) {
		this->updateShape(level, x, y, z);
		return Tile::getTileAABB(level, x, y, z);
	}
	virtual bool_t isSolidRender() {
		return 0;
	}
	virtual bool_t isPathfindable(LevelSource*, int32_t, int32_t, int32_t) {
		return 1;
	}
	virtual int32_t getTileEntityType() {
		return 4;
	}
	virtual void neighborChanged(Level* a2, int32_t x, int32_t y, int32_t z, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
		int32_t v16; // r1
		int32_t v17; // r2
		int32_t v18; // r0
		Material* v20; // r0
		int32_t v22; // r0
		if (this->field_80) {
			v16 = x;
			v17 = y - 1;
			LABEL_8: v20 = a2->getMaterial(v16, v17, z);
			goto LABEL_9;
		}
		v18 = a2->getData(x, y, z);
		if (v18 == 2) {
			v20 = a2->getMaterial(x, y, z + 1);
			goto LABEL_9;
		}
		if (v18 != 3) {
			if (v18 == 4) {
				v16 = x + 1;
			} else {
				if (v18 != 5) {
					goto LABEL_10;
				}
				v16 = x - 1;
			}
			v17 = y;
			goto LABEL_8;
		}
		v20 = a2->getMaterial(x, y, z - 1);
		LABEL_9: if (!v20->isSolid()) {
			LABEL_10: v22 = a2->getData(x, y, z);
			this->spawnResources(a2, x, y, z, v22, 1.0);
			a2->setTile(x, y, z, 0, 3);
		}
		Tile::neighborChanged(a2, x, y, z, a6, a7, a8, a9);
	}
	virtual int32_t getResource(int32_t, Random*) {
		return Item::sign->itemID;
	}

};
