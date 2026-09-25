#pragma once
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>

struct StoneTile : Tile{
	StoneTile(int32_t a2, const std::string& a3) :
			Tile(a2, a3, Material::stone) {
	}

	virtual ~StoneTile() {
	}
	virtual int32_t getResource(int32_t, struct Random*) {
		return Tile::stoneBrick->blockID;
	}

};
