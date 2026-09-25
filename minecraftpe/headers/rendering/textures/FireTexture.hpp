#pragma once
#include <rendering/textures/DynamicTexture.hpp>
#include <util/Random.hpp>

struct FireTexture: DynamicTexture
{
	static const float fireDieRate;
	float* field_28, * field_2C;
	Random random;

	FireTexture();

	virtual ~FireTexture();
	virtual void tick();
};
