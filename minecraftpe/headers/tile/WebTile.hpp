#pragma once
#include <tile/Tile.hpp>
#include <item/Item.hpp>
#include <entity/Entity.hpp>

struct WebTile : Tile{
	WebTile(int32_t id, const std::string& name, Material* mat) : Tile(id, name, mat){

	}

	virtual ~WebTile() {
	}
	virtual bool_t isCubeShaped() {
		return 0;
	}
	virtual int32_t getRenderShape() {
		return 1;
	}
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t) {
		return 0;
	}
	virtual bool_t isSolidRender() {
		return 0;
	}
	virtual int32_t getResource(int32_t, Random*) {
		return Item::string->itemID;
	}
	virtual int32_t getRenderLayer() {
		return 1;
	}
	virtual void entityInside(Level*, int32_t, int32_t, int32_t, Entity* entity) {
		entity->makeStuckInWeb();
	}

};
