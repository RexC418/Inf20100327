#pragma once
#include <item/Item.hpp>
#include <entity/Mob.hpp>

struct SaddleItem: Item
{
	SaddleItem(int32_t id) :
			Item(id) {
		this->maxStackSize = 1;
	}
	virtual ~SaddleItem() {
	}
	virtual void hurtEnemy(ItemInstance* a2, Mob* a3, Mob* a4) {
		if (a4->isPlayer()) {
			this->interactEnemy(a2, a3, (Player*) (a4));
		}
	}
	virtual void interactEnemy(ItemInstance*, Mob*, Player*) {
	}
};
