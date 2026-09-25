#pragma once
#include <tile/Tile.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

struct MultiTextureTile: Tile
{
	TextureAtlasTextureItem field_7C;
	int32_t field_A8;

	MultiTextureTile(int32_t a2, std::string a3, const struct Material* a4) :
			Tile(a2, a4) {
		this->field_7C = *this->getTextureItem(a3);
		this->field_A8 = this->field_7C.getUVCount();
	}

	virtual ~MultiTextureTile() {
	}
	const virtual TextureUVCoordinateSet* getTexture(int32_t a2, int32_t a3) {
		if (a3 < 0 || a3 >= this->field_A8) {
			return &this->textureUV;
		} else {
			return this->field_7C.getUV(a3);
		}
	}
	virtual int32_t getSpawnResourcesAuxValue(int32_t a2) {
		return a2;
	}
};
