#pragma once
#include <_types.h>

struct BuildActionIntention
{
	int32_t field_0;

	bool_t isRemove() {
		int32_t v1; // r0
		v1 = this->field_0;
		if ((v1 & 4) != 0) {
			return 1;
		} else {
			return ((uint32_t) (v1) >> 1) & 1;
		}
	}
};
