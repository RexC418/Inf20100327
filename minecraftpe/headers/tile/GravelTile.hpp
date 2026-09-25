#pragma once
#include <tile/HeavyTile.hpp>
#include <item/Item.hpp>

struct GravelTile : HeavyTile{
	GravelTile(int32_t id, const std::string& s) :
			HeavyTile(id, s) {
	}
	virtual ~GravelTile() {
	}
	virtual int getResource(int32_t a2, Random* a3) {
		if (a3->genrand_int32() % 0xa) return this->blockID;

		return Item::flint->itemID;
	}
};
