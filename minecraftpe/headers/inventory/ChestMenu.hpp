#pragma once
#include <inventory/ContainerMenu.hpp>
#include <tile/entity/ChestTileEntity.hpp>

struct ChestMenu: ContainerMenu
{
	ChestTileEntity* field_24;
	int32_t field_28;
	ChestMenu(ChestTileEntity* a2) :
			ContainerMenu(a2, a2->id) {
		this->field_24 = a2;
		this->field_28 = -1;
		if (a2->pair) {
			this->field_28 = a2->pair->id;
		}
	}

	virtual ~ChestMenu() {
	}
	virtual bool_t tileEntityDestroyedIsInvalid(int32_t a2) {
		return this->field_1C == a2 || this->field_28 == a2;
	}
};
