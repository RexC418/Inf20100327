#pragma once
#include <entity/Entity.hpp>

struct Entity;
struct DistanceEntitySorter
{
	float x, y, z;
	bool_t operator ()(const Entity* a2, const Entity* a3) {
		return (float) (((float) (((float) (((float) ((a2->posY - this->y)) * (float) ((a2->posY - this->y)))) + (float) (((float) ((a2->posX - this->x)) * (float) ((a2->posX - this->x)))))) + (float) (((float) ((a2->posZ - this->z)) * (float) ((a2->posZ - this->z)))))) < (float) (((float) (((float) (((float) ((a3->posY - this->y)) * (float) ((a3->posY - this->y)))) + (float) (((float) ((a3->posX - this->x)) * (float) ((a3->posX - this->x)))))) + (float) (((float) ((a3->posZ - this->z)) * (float) ((a3->posZ - this->z))))));
	}
};
