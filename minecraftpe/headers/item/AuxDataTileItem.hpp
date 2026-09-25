#pragma once
#include <item/TileItem.hpp>
#include <tile/Tile.hpp>
#include <I18n.hpp>

struct AuxDataTileItem: TileItem
{
	Tile* tile;

	AuxDataTileItem(int32_t id, Tile* t) :
			TileItem(id) {
		this->tile = t;
		this->setMaxDamage(0);
		this->setStackedByData(1);
	}

	virtual ~AuxDataTileItem() {
	}
	const virtual TextureUVCoordinateSet* getIcon(int32_t a2, int32_t a3, bool_t a4) const {
		return this->tile->getCarriedTexture(2, a2);
	}
	virtual int32_t getLevelDataForAuxValue(int32_t a2) const {
		return a2;
	}
	virtual std::string getName(const ItemInstance* a2) const {
		std::string v9 = this->tile->getTypeDescriptionId(a2->getAuxValue());
		if (v9.length()) {
			return I18n::get(this->getDescriptionId() + "." + v9 + ".name");
		} else {
			return Item::getName(a2);
		}
	}
	virtual std::string getDescription(const ItemInstance* a2) const {
		std::string v10 = this->tile->getTypeDescriptionId(a2->getAuxValue());
		if (v10.length()) {
			return this->getDescriptionId() + "." + v10;
		} else {
			return Item::getDescription(a2);
		}
	}

};
