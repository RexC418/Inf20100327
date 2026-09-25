#pragma once
#include <tile/Tile.hpp>
#include <item/Item.hpp>

struct BookshelfTile : Tile{
	TextureUVCoordinateSet uv;

	BookshelfTile(int32_t id, std::string a2, const struct Material* a3) :
			Tile(id, a2, a3) {
		this->uv = this->getTextureUVCoordinateSet("planks", 0);
	}
	virtual ~BookshelfTile() {
	}
	virtual TextureUVCoordinateSet* getTexture(int32_t a2) {
		if (a2 > 1) return &this->textureUV;

		return &this->uv;
	}
	virtual int32_t getResource(int32_t a2, Random* a3) {
		return Item::book->itemID;
	}
	virtual int32_t getResourceCount(Random*) {
		return 3;
	}

};
