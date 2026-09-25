#pragma once
#include <item/TileItem.hpp>
#include <tile/Tile.hpp>
#include <I18n.hpp>
#include <item/DyePowderItem.hpp>

struct ClothTileItem: TileItem
{
	ClothTileItem(int32_t id) :
			TileItem(id) {
		this->setMaxDamage(0);
		this->setStackedByData(1);
	}
	virtual ~ClothTileItem(){}
	const virtual TextureUVCoordinateSet* getIcon(int32_t a2, int32_t, bool_t) const {
		return Tile::cloth->getTexture(2, a2);
	}
	virtual int32_t getLevelDataForAuxValue(int32_t a2) const {
		return a2;
	}
	virtual std::string getName(const ItemInstance* a3) const {
		return I18n::get(TileItem::getDescriptionId() + "." + DyePowderItem::COLOR_DESCS[(~a3->getAuxValue()) & 0xF] + ".name");
	}
	virtual std::string getDescriptionId(const ItemInstance* a3) const{
		return TileItem::getDescriptionId() + "." + DyePowderItem::COLOR_DESCS[(~a3->getAuxValue()) & 0xF];
	}

};
