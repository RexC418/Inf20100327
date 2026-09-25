#pragma once
#include <tile/Tile.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>
#include <tile/material/Material.hpp>

struct ClothTile : Tile{
	TextureAtlasTextureItem tex;
	ClothTile(int32_t id) :
			Tile(id, Material::cloth) {
		this->tex = *this->getTextureItem("wool");
		this->textureUV = *this->tex.getUV(0);
	}

	virtual ~ClothTile() {
	}
	const virtual TextureUVCoordinateSet* getTexture(int32_t a2, int32_t a3) {
		if (a3) return this->tex.getUV(a3);

		return &this->textureUV;
	}
	virtual int32_t getSpawnResourcesAuxValue(int32_t a2) {
		return a2;
	}
};
