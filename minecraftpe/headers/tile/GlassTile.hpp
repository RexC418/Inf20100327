#pragma once
#include <tile/HalfTransparentTile.hpp>

struct GlassTile: HalfTransparentTile
{
	int8_t field_81, field_82, field_83;

	GlassTile(int32_t id, const std::string& s, Material* m) :
			HalfTransparentTile(id, s, m) {
	}

	virtual ~GlassTile() {
	}
	virtual int32_t getRenderLayer() {
		return 1;
	}
	virtual int32_t getResourceCount(Random*) {
		return 0;
	}
};
