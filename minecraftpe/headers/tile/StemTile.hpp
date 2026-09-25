#pragma once
#include <tile/Bush.hpp>

struct StemTile : Bush{
	Tile* grownTile;
	TextureUVCoordinateSet field_84, field_9C;

	StemTile(int32_t, Tile*);

	int32_t getConnectDir(LevelSource*, int32_t, int32_t, int32_t);
	TextureUVCoordinateSet* getConnectedTexture();
	float getGrowthSpeed(Level*, int32_t, int32_t, int32_t);

	virtual ~StemTile() {
	}
	virtual bool_t onFertilized(Level* level, int32_t x, int32_t y, int32_t z) {
		int32_t v8; // r8
		int32_t v9; // r3
		v8 = level->getData(x, y, z);
		v9 = level->random.genrand_int32() % 3 + v8 + 2;
		if (v9 >= 7) {
			v9 = 7;
		}
		level->setData(x, y, z, v9, 2);
		return 1;
	}
	virtual int32_t getRenderShape();
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t);
	virtual void updateDefaultShape();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
	virtual void spawnResources(Level*, int32_t, int32_t, int32_t, int32_t, float);
	virtual int32_t getColor(int32_t);
	virtual int32_t getColor(LevelSource*, int32_t, int32_t, int32_t);
	virtual bool_t mayPlaceOn(int32_t);
};
