#pragma once
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <entity/Player.hpp>

struct FoodItem: Item
{
	int32_t healAmount;
	float field_48;
	int8_t field_4C, field_4D, field_4E, field_4F;

	FoodItem(int32_t id, int32_t healAmount, float f48, int8_t f4C)
		: Item(id) {
		this->field_48 = f48;
		this->field_4C = f4C;
		this->healAmount = healAmount;
	}
	virtual ~FoodItem() {
	}

	virtual ItemInstance* use(ItemInstance* a2, struct Level* a3, Player* a4) {
		if(!a4->abilities.invulnerable && a4->isHurt()) {
			a4->startUsingItem(ItemInstance(*a2), this->getMaxUseDuration());
		}
		return a2;
	}
	virtual int32_t getMaxUseDuration() const {
		return 32;
	}
	virtual ItemInstance useTimeDepleted(ItemInstance* a2, Level* level, Player* player) {
		--a2->count;
		player->heal(this->healAmount);
		level->playSound(player, "random.burp", 0.5, level->random.nextFloat()*0.1 + 0.9);
		return ItemInstance(*a2);
	}
	virtual int32_t getUseAnimation() const {
		return 1;
	}
	virtual bool_t isFood() const {
		return 1;
	}
};
