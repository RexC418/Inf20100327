#pragma once
#include <tile/Tile.hpp>

struct InvisibleTile : Tile{

	InvisibleTile(int32_t id, const std::string& name, Material* mat) :
			Tile(id, name, mat) {
	}

	virtual ~InvisibleTile() {
	}
	virtual int32_t getRenderShape() {
		return -1;
	}
};
