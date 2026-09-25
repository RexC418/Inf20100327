#pragma once
#include <tile/Tile.hpp>

struct RotatedPillarTile: Tile
{
	RotatedPillarTile(int32_t id, const struct Material* mat);
	virtual ~RotatedPillarTile() {
	}
	virtual int32_t getRenderShape();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual int32_t getPlacementDataValue(Level*, int32_t, int32_t, int32_t, int32_t, float, float, float, Mob*, int32_t);
	virtual TextureUVCoordinateSet* getDirTexture(int32_t, int32_t);
};
