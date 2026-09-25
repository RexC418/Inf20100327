#pragma once
#include <item/TileItem.hpp>

struct LeafTileItem: TileItem
{
	LeafTileItem(int32_t id) :
			TileItem(id) {
		this->setMaxDamage(0);
		this->setStackedByData(1);
	}

	virtual ~LeafTileItem(){}
	const virtual TextureUVCoordinateSet* getIcon(int32_t a2, int32_t, bool_t) const {
		return Tile::leaves->getTexture(0, a2);
	}
	virtual int32_t getLevelDataForAuxValue(int32_t a2) const {
		return a2 | 8;
	}

};
