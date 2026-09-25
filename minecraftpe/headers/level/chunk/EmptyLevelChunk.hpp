#pragma once
#include <level/chunk/LevelChunk.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>
#include <string.h>

struct EmptyLevelChunk: LevelChunk
{
	EmptyLevelChunk(Level* level) :
			LevelChunk(level, 0, 0, 0) {
		this->field_24A = 1;
	}
	virtual ~EmptyLevelChunk() {
	}
	virtual bool_t isAt(int32_t x, int32_t z) {
		return x == this->chunkX && z == this->chunkZ;
	}
	virtual int32_t getHeightmap(int32_t, int32_t) {
		return 0;
	}
	virtual void recalcHeightmap() {
	}
	virtual void recalcHeightmapOnly() {
	}
	virtual int32_t getBrightness(const struct LightLayer&, int32_t, int32_t, int32_t) {
		return 7;
	}
	virtual void setBrightness(const struct LightLayer&, int32_t, int32_t, int32_t, int32_t) {
	}
	virtual int32_t getRawBrightness(int32_t, int32_t, int32_t, int32_t) {
		return 7;
	}
	virtual void addEntity(struct Entity*) {
	}
	virtual void removeEntity(struct Entity*) {
	}
	virtual void removeEntity(struct Entity*, int32_t) {
	}
	virtual bool_t isSkyLit(int32_t, int32_t, int32_t) {
		return 0;
	}
	virtual void lightLava() {
	}
	virtual void recalcBlockLights() {
	}
	virtual void skyBrightnessChanged() {
	}
	virtual void load() {
	}
	virtual void unload() {
	}
	virtual void markUnsaved() {
	}
	virtual void getEntities(struct Entity*, const struct AABB&, std::vector<struct Entity*>&) {
	}
	virtual int32_t getTile(int32_t, int32_t, int32_t) {
		return Tile::invisible_bedrock->blockID;
	}
	virtual bool_t setTile(int32_t, int32_t, int32_t, int32_t) {
		return 1;
	}
	virtual bool_t setTileAndData(int32_t, int32_t, int32_t, int32_t, int32_t) {
		return 1;
	}
	virtual int32_t getData(int32_t, int32_t, int32_t) {
		return 0;
	}
	virtual bool_t setData(int32_t, int32_t, int32_t, int32_t) {
		return 0;
	}
	virtual void setBlocks(uint8_t*, int32_t) {
	}
	virtual int32_t getBlocksAndData(uint8_t* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
		int32_t v9 = (a8 - a5) * (a6 - a3) * (a7 - a4);
		int32_t v10 = v9 + 3 * (v9 / 2);
		memset(&a2[a9], Tile::invisible_bedrock->blockID, v10);
		return v10;
	}
	virtual int32_t setBlocksAndData(uint8_t* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
		int32_t v9 = (a8 - a5) * (a6 - a3) * (a7 - a4);
		return v9 + 3 * (v9 / 2);
	}
	virtual Random getRandom(long a3) {
		return Random((this->level->getSeed() + 4987142 * this->chunkX * this->chunkX + 5947611 * this->chunkX + 4392871 * this->chunkZ * this->chunkZ + 389711 * this->chunkZ) ^ a3);
	}
	virtual bool_t isEmpty() {
		return 1;
	}
};
