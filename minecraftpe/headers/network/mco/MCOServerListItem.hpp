#pragma once
#include <_types.h>
#include <string>
#include <map>
#include <vector>

struct MCOServerListItem
{
	int64_t field_0;
	std::string worldName;
	bool_t field_C;
	int8_t field_D, field_E, field_F;
	std::string field_10;
	bool_t field_14;
	int8_t field_15, field_16, field_17;
	int32_t field_18;
	std::string gamemodeName;
	std::vector<std::string> field_20;
	std::map<std::string, std::string> field_2C;

	MCOServerListItem(const MCOServerListItem&) {
		printf("MCOServerListItem::MCOServerListItem(const MCOServerListItem&) - not implemented\n");
	}
	MCOServerListItem(MCOServerListItem&&) {
		printf("MCOServerListItem::MCOServerListItem(MCOServerListItem&&) - not implemented\n");
	}
	MCOServerListItem() {
		this->worldName = "My World";
		this->gamemodeName = "creative";
	}

	MCOServerListItem& operator =(const MCOServerListItem& a2) {
		this->field_0 = a2.field_0;
		this->worldName = a2.worldName;
		this->field_C = a2.field_C;
		this->field_10 = a2.field_10;
		this->field_14 = a2.field_14;
		this->field_18 = a2.field_18;
		this->gamemodeName = a2.gamemodeName;
		this->field_20 = a2.field_20;
		this->field_2C = a2.field_2C;
		return *this;
	}
	MCOServerListItem& operator =(MCOServerListItem&&) {
		printf("MCOServerListItem::operator=(MCOServerListItem&&) - not implemented\n");
		return *this;
	}
	~MCOServerListItem(){}
};
