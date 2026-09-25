#pragma once
#include <_types.h>
#include <rendering/frustum/FrustumData.hpp>
#include <math/AABB.hpp>

struct FrustumCuller{
	FrustumData data;
	float xOff, yOff, zOff;

	bool_t isVisible(const AABB& bb) {
		return this->data.cubeInFrustum(bb.minX - this->xOff, bb.minY - this->yOff, bb.minZ - this->zOff, bb.maxX - this->xOff, bb.maxY - this->yOff, bb.maxZ - this->zOff);
	}
};
