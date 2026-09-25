#pragma once
#include <level/Level.hpp>
#include <string>

struct Font;
struct EntityRenderDispatcher;
struct Entity;
struct AABB;

struct EntityRenderer
{
	static EntityRenderDispatcher* entityRenderDispatcher;

	EntityRenderer();
	void bindTexture(const std::string&);
	Font* getFont();
	void init(EntityRenderDispatcher*);
	bool_t isFancy();
	static void render(const AABB&, float, float, float);
	void renderFlame(Entity* e, float x, float y, float z, float);
	static void renderFlat(const AABB&);

	virtual ~EntityRenderer();
	virtual void render(Entity*, float, float, float, float, float) = 0;
	virtual void postRender(Entity*, float, float, float, float, float);
	virtual void renderName(Entity*, float) {
	}

};
