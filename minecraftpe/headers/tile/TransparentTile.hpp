#pragma once
#include <tile/Tile.hpp>
#include <level/LevelSource.hpp>

struct TransparentTile : Tile{
	bool_t field_7C;
	char field_7D, field_7E, field_7F;

	TransparentTile(int32_t id, const std::string& s, Material* mat)
		: Tile(id, s, mat) {
		this->field_7C = 0; //TODO check is it actually here
	}

	virtual ~TransparentTile() {
	}

	virtual bool_t shouldRenderFace(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t face) {
		int32_t v10; // r0

		v10 = level->getTile(x, y, z);
		if(!this->field_7C && v10 == this->blockID) {
			return this->field_7C;
		} else {
			return Tile::shouldRenderFace(level, x, y, z, face);
		}
	}
	virtual bool_t isSolidRender() {
		return 0;
	}
};
