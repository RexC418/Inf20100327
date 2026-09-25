#pragma once
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>

struct MetalTile : Tile{
	MetalTile(int32_t id, const std::string& a3) : Tile(id, a3, Material::metal) {
	}

	virtual ~MetalTile(){}
	virtual TextureUVCoordinateSet* getTexture(int32_t) {
		return &this->textureUV;
	}

};
