#pragma once
#include <tile/Tile.hpp>
#include <item/Item.hpp>


struct ClayTile : Tile{
	ClayTile(int32_t id, std::string n, Material* m) :
			Tile(id, n, m) {
		this->field_5C = 255;
	}

	virtual ~ClayTile() {
	}
	virtual int32_t getResource(int32_t, Random*) {
		return Item::clay->itemID;
	}
	virtual int32_t getResourceCount(Random*) {
		return 4;
	}
};
