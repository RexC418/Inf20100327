#pragma once
#include <item/Item.hpp>
#include <vector>
//- one shall not include stuff in the header
//*evil mojang making compilation slower(20s => 30s </3)*
//*could have simply used __attribute__(weak) or whatever the syntax is </3
#include <tile/Tile.hpp>

struct Tile;
struct DiggerItem: Item
{
	float efficiencyMultiplier;
	const Item::Tier* tier;
	int32_t damageAgainstEntity;
	std::vector<Tile*> field_50;
	bool_t field_5C[256];

	void setTiles(const std::vector<Tile*>& a2) {
		for(int i = 0; i != 256; ++i) {
			this->field_5C[i] = 0;
		}

		for(Tile* t: a2) {
			this->field_5C[t->blockID] = 1;
		}
		this->field_50 = a2;
	}


	DiggerItem(int32_t a2, int addDmg, const Item::Tier& a3, const std::vector<Tile*>& tiles)
		: Item(a2)
		, tier(&a3)
		, efficiencyMultiplier(a3.efficienctMultiplier){
		this->setTiles(tiles);
		this->maxStackSize = 1;
		this->setMaxDamage(a3.durability);
		this->damageAgainstEntity = a3.damageAgainstEntity + addDmg;
	}
	virtual ~DiggerItem() {
	}

	virtual float getDestroySpeed(ItemInstance* a2, Tile* a3) {
		if(a3 && this->field_5C[a3->blockID]) {
			return this->efficiencyMultiplier;
		} else {
			return 1.0;
		}
	}
	virtual int32_t getAttackDamage(Entity*) {
		return this->damageAgainstEntity;
	}
	virtual void hurtEnemy(ItemInstance* a2, Mob* a3, Mob* a4) {
		a2->hurtAndBreak(2, a4);
	}
	virtual bool_t mineBlock(ItemInstance* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, Mob* a7) {
		a2->hurtAndBreak(1, a7);
		return 1;
	}
	virtual bool_t isHandEquipped() const{
		return 1;
	}

};
