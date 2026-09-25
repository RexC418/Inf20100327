#pragma once
#include <rendering/entity/EntityRenderer.hpp>
#include <AppPlatform.hpp>
#include <rendering/MeshBuffer.hpp>

struct ArrowRenderer: EntityRenderer, AppPlatform::Listener
{
	MeshBuffer field_8;

	ArrowRenderer() :
			EntityRenderer(), field_8() {
		AppPlatform::_singleton->addListener(this, 1);
	}

	virtual ~ArrowRenderer() {
		AppPlatform::_singleton->removeListener(this);
	}
	virtual void render(Entity*, float, float, float, float, float);
	virtual void onAppSuspended() {
		this->field_8.reset();
	}
};
