#pragma once
#include <util/area/IArea.hpp>
#include <vector>

struct IncludeExcludeArea: IArea
{
	std::vector<IArea*> includeAreas;
	std::vector<IArea*> excludeAreas;

	virtual ~IncludeExcludeArea() {
		IncludeExcludeArea::clear();
		//TODO i wonder how to force std::vector<IArea *>::~vector to be sub_XXXXX here
	}
	virtual bool_t isInside(float x, float y) {
		uint32_t i, j;
		IArea *area1, *area2;
		for (i = 0; i < this->includeAreas.size(); ++i) {
			area1 = this->includeAreas[i];
			if (area1->isInside(x, y)) goto SKIP_RETURN;

			LABEL_9:
			//
			;
		}
		return 0;
		SKIP_RETURN: for (i = 0; i < this->excludeAreas.size(); ++i) {
			area2 = this->excludeAreas[i];
			if (area2->isInside(x, y)) goto LABEL_9;
		}
		return 1;
	}
	virtual void clear() {
		if (this->field_4) {
			for (uint32_t i = 0; i < this->includeAreas.size(); ++i) {
				IArea* area = this->includeAreas[i];
				if (area->field_4) delete area;
			}
			for (uint32_t i = 0; i < this->excludeAreas.size(); ++i) {
				IArea* area = this->excludeAreas[i];
				if (area->field_4) delete area;
			}
		}
		this->includeAreas.clear();
		this->excludeAreas.clear();
	}
};
