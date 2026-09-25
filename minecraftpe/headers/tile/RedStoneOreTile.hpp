#pragma once
#include <tile/Tile.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>

struct RedStoneOreTile : Tile{
	bool_t emitLight;
	char field_81, field_82, field_83;

	RedStoneOreTile(int32_t a2, const std::string& a3, bool_t glowing) :
			Tile(a2, a3, Material::stone) {
		if (glowing) this->setTicking(1);

		this->emitLight = glowing;
	}

	void interact(Level* level, int32_t x, int32_t y, int32_t z) {
		this->poofParticles(level, x, y, z);
		if (this->blockID == Tile::redStoneOre->blockID) {
			level->setTile(x, y, z, Tile::redStoneOre_lit->blockID, 2);
		}
	}
	void poofParticles(Level* level, int32_t x, int32_t y, int32_t z) {
		float v5; // s20
		Random* p_random; // r9
		int32_t i; // r5
		float v11; // s17
		float v12; // s18
		float v13; // s21
		float v14; // s19
		v5 = (float) (x);
		for (i = 0; i != 6; ++i) {
			v11 = v5 + level->random.nextFloat();
			v12 = (float) (y) + level->random.nextFloat();
			v13 = (float) (z);
			v14 = (float) (z) + level->random.nextFloat();
			if (i) {
				switch (i) {
				case 1:
					if (!level->isSolidBlockingTile(x, y - 1, z)) {
						v12 = (float) (y) - 0.0625;
					}
					break;
				case 2:
					if (!level->isSolidBlockingTile(x, y, z + 1)) {
						v14 = (float) ((z + 1)) + 0.0625;
					}
					break;
				case 3:
					if (!level->isSolidBlockingTile(x, y, z - 1)) {
						v14 = v13 - 0.0625;
					}
					break;
				case 4:
					if (!level->isSolidBlockingTile(x + 1, y, z)) {
						v11 = (float) ((x + 1)) + 0.0625;
					}
					break;
				default:
					if (i == 5 && !level->isSolidBlockingTile(x - 1, y, z)) {
						v11 = v5 - 0.0625;
					}
					break;
				}
			} else if (!level->isSolidBlockingTile(x, y + 1, z)) {
				v12 = (float) ((y + 1)) + 0.0625;
			}

			if (v11 < v5 || v11 > (float) ((x + 1)) || v12 < 0.0 || v12 > (float) ((y + 1)) || v14 < v13 || v14 > (float) ((z + 1))) {
				level->addParticle(PT_RED_DUST, v11, v12, v14, 0.0, 0.0, 0.0, 0);
			}
		}
	}

	virtual ~RedStoneOreTile() {
	}
	virtual int32_t getTickDelay() {
		return 30;
	}
	virtual void tick(Level* level, int32_t x, int32_t y, int32_t z, Random*) {
		if (this->blockID == Tile::redStoneOre_lit->blockID) {
			level->setTile(x, y, z, Tile::redStoneOre->blockID, 2);
		}
	}
	virtual void animateTick(Level* level, int32_t x, int32_t y, int32_t z, Random*) {
		if (this->emitLight) this->poofParticles(level, x, y, z);
	}
	virtual int32_t getResource(int32_t, Random*) {
		return Item::redStone->itemID;
	}
	virtual int32_t getResourceCount(Random* a2) {
		return (a2->genrand_int32() & 1) + 4;
	}
	virtual bool_t use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
		this->interact(level, x, y, z);
		return Tile::use(level, x, y, z, player);
	}
	virtual void stepOn(Level* level, int32_t x, int32_t y, int32_t z, Entity*) {
		this->interact(level, x, y, z);
	}
	virtual void attack(Level* level, int32_t x, int32_t y, int32_t z, Player*) {
		this->interact(level, x, y, z);
	}
};
