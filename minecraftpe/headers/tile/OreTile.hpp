#pragma once
#include <tile/Tile.hpp>
#include <util/Random.hpp>
#include <item/Item.hpp>
#include <tile/material/Material.hpp>

struct OreTile : Tile{
	OreTile(int32_t a2, const std::string& a3) :
			Tile(a2, a3, Material::stone) {
	}

	virtual ~OreTile() {
	}
	virtual int32_t getResource(int32_t a2, Random* a3) {
		int32_t result; // r0
		Item* v4;
		result = this->blockID;
		if (result == Tile::coalOre->blockID) {
			v4 = Item::coal;
		} else if (result == Tile::emeraldOre->blockID) {
			v4 = Item::emerald;
		} else {
			if (result != Tile::lapisOre->blockID) {
				return result;
			}
			v4 = Item::dye_powder;
		}

		return v4->itemID;
	}
	virtual int32_t getResourceCount(Random* a2) {
		if (this->blockID == Tile::lapisOre->blockID) {
			return a2->genrand_int32() % 5 + 4;
		} else {
			return 1;
		}
	}
	virtual int32_t getSpawnResourcesAuxValue(int32_t a2) {
		if (this->blockID == Tile::lapisOre->blockID) {
			return 4;
		} else {
			return 0;
		}
	}
};
