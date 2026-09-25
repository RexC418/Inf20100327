#pragma once
#include <_types.h>
#include <item/ItemInstance.hpp>

struct CraftingContainer
{
	//TODO find out the structure of this thing
	void* field_0;
	int field_4, field_8, field_C, field_10, field_14;
	ItemInstance* getItem(int32_t a2, int32_t a3) {
		if(a2 < 0) return 0;
		if(a3 >= this->field_14) return 0;
		//TODO find what is field_0
		printf("CraftingContainer::getItem - not implemented <!>\n");
		return 0;
	}
};
