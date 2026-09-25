#pragma once
#include <tile/Tile.hpp>

struct DirectionalTile : Tile{
	DirectionalTile(int32_t id, const Material* mat) :
			Tile(id, mat) {
	}
	virtual ~DirectionalTile() {
	}
};
