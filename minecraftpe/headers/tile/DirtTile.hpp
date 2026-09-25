#pragma once
#include <tile/Tile.hpp>

struct DirtTile : Tile{
	DirtTile(int32_t id, std::string n, Material* m) :
			Tile(id, n, m) {
		this->field_5C = 255;
	}
	virtual ~DirtTile() {
	}
};
