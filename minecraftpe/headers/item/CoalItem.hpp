#pragma once
#include <item/Item.hpp>

struct CoalItem: Item
{
	TextureUVCoordinateSet field_48;

	CoalItem(int32_t id) :
			Item(id) {
		this->setStackedByData(1);
		this->setMaxDamage(0);
		this->field_48 = Item::getTextureUVCoordinateSet("charcoal", 0);
	}
	virtual ~CoalItem(){}
	const virtual TextureUVCoordinateSet* getIcon(int32_t a2, int32_t, bool_t) const {
		if (a2 == 1) return &this->field_48;

		return &this->iconUV;
	}
	virtual std::string getDescriptionId(const ItemInstance* a3) const {
		if (a3->getAuxValue() == 1) {
			return Item::ICON_DESCRIPTION_PREFIX + "charcoal";
		}
		return Item::ICON_DESCRIPTION_PREFIX + "coal";
	}
};
