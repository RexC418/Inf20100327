#pragma once
#include <tile/Tile.hpp>

struct WallTile : Tile{
	static const float WALL_WIDTH, WALL_HEIGHT, POST_WIDTH, POST_HEIGHT;
	WallTile(int32_t, Tile*);
	bool_t connectsTo(LevelSource*, int32_t, int32_t, int32_t);

	virtual ~WallTile(){}
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t);
	virtual bool_t shouldRenderFace(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual const TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual int32_t getSpawnResourcesAuxValue(int32_t);
};
