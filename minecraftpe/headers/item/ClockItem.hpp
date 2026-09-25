#pragma once
#include <item/Item.hpp>
#include <entity/Mob.hpp>
#include <level/Level.hpp>

struct ClockItem: Item
{
	TextureUVCoordinateSet textures[64];

	ClockItem(int32_t id) :
			Item(id) {
		this->itemTexture = "watch-atlas.png";
		this->field_C = 64;
		int32_t v4 = 0;
		do {
			int32_t v9 = v4++;
			for (int32_t i = 0; i != 8;) {
				int32_t v5 = i;
				int32_t v6 = v4 - 1 + 8 * i++;
				TextureUVCoordinateSet* tex = &this->textures[v6];
				tex->minY = (float) (v9) * 0.125;
				tex->maxY = (float) (v4) * 0.125;
				tex->height = 128;
				tex->width = 128;
				tex->minX = (float) (v5) * 0.125;
				tex->maxX = (float) (i) * 0.125;
			}
		} while (v4 != 8);
	}

	virtual ~ClockItem() {
	}
	const virtual TextureUVCoordinateSet* getIcon(int32_t a2, int32_t a3, bool_t a4) const {
		if (a4) return &this->iconUV;

		return &this->textures[a3];
	}
	virtual int32_t getAnimationFrameFor(Mob* a2) const {
		return (int32_t) ((float) ((a2->level->getTimeOfDay(1.0) * (float) (this->field_C))));
	}
};
