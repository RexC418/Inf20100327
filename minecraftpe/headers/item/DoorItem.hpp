#pragma once
#include <item/Item.hpp>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>

struct DoorItem: Item
{
	struct Material* field_48;
	static void place(Level* level, int32_t x, int32_t y, int32_t z, int32_t dir, struct Tile* tile) {
		int32_t zoff; // r7
		int32_t xoff; // r9
		int32_t v12; // r11
		bool_t v14; // r7
		bool_t v15; // r11
		int32_t v16; // r2
		int32_t v17; // [sp+14h] [bp-44h]
		int32_t v21; // [sp+28h] [bp-30h]
		int32_t v22; // [sp+2Ch] [bp-2Ch]
		if (dir == 0) {
			zoff = 1;
			xoff = 0;
		} else if (dir == 1) {
			zoff = 0;
			xoff = -1;
		} else if (dir == 2) {
			zoff = -1;
			xoff = 0;
		} else if (dir == 3) {
			zoff = 0;
			xoff = 1;
		} else {
			zoff = 0;
			xoff = 0;
		}

		v12 = level->isSolidBlockingTile(x - xoff, y, z - zoff);
		v21 = v12 + level->isSolidBlockingTile(x - xoff, y + 1, z - zoff);
		v17 = level->isSolidBlockingTile(xoff + x, y, z + zoff);
		v22 = v17 + level->isSolidBlockingTile(xoff + x, y + 1, z + zoff);
		v14 = level->getTile(x - xoff, y, z - zoff) == tile->blockID || level->getTile(x - xoff, y + 1, z - zoff) == tile->blockID;
		v15 = level->getTile(xoff + x, y, z + zoff) != tile->blockID && level->getTile(xoff + x, y + 1, z + zoff) != tile->blockID && v14 || v22 > v21;
		level->setTileAndData(x, y, z, tile->blockID, dir, 2);
		if (v15) {
			v16 = 0x9;
		} else {
			v16 = 0x8;
		}
		level->setTileAndData(x, y + 1, z, tile->blockID, v16, 2);
		level->updateNeighborsAt(x, y, z, tile->blockID);
		level->updateNeighborsAt(x, y + 1, z, tile->blockID);
	}
	DoorItem(int32_t id, Material* mat) :
			Item(id) {
		this->field_48 = mat;
		this->maxItemdamage = 64;
		this->maxStackSize = 1;
	}

	virtual ~DoorItem() {
	}
	virtual bool_t useOn(ItemInstance* item, Player* player, Level* level, int32_t x, int32_t y, int32_t z, int32_t face, float fx, float fy, float fz) {
		Tile* v15; // r4
		float v17; // s15
		int32_t v18; // r5
		if (face != 1) {
			return 0;
		}
		if (this->field_48 == Material::wood) {
			v15 = Tile::door_wood;
		} else {
			v15 = Tile::door_iron;
		}
		if (v15->mayPlace(level, x, y + 1, z)) {
			v17 = (float) (((float) (((float) ((player->yaw + 180.0)) * 4.0)) / 360.0)) - 0.5;
			v18 = (int32_t) (v17);
			if (v17 < (float) ((int) (v17))) {
				v18 = v18 - 1;
			}
			DoorItem::place(level, x, y + 1, z, v18 & 3, v15);
			--item->count;
			return 1;
		}
		return 0;
	}

};
