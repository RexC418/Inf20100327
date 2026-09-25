#pragma once
#include <_types.h>
#include <string>

struct LevelSummary
{
	std::string worldName, field_4;
	int32_t field_8, gamemode, field_10, field_14;

	LevelSummary() {
		this->worldName = "";
		this->field_4 = "";
	}
	LevelSummary(const LevelSummary& a2) {
		this->worldName = a2.worldName;
		this->field_4 = a2.field_4;
		this->field_8 = a2.field_8;
		this->gamemode = a2.gamemode;
		this->field_10 = a2.field_10;
		this->field_14 = a2.field_14;
	}
	LevelSummary(LevelSummary&& a2) {
		this->worldName = a2.worldName;
		this->field_4 = a2.field_4;
		a2.worldName = "";
		a2.field_4 = "";
		this->field_8 = a2.field_8;
		this->gamemode = a2.gamemode;
		this->field_10 = a2.field_10;
		this->field_14 = a2.field_14;
	}
	LevelSummary& operator =(const LevelSummary& a2) {
		this->worldName = a2.worldName;
		this->field_4 = a2.field_4;
		this->field_8 = a2.field_8;
		this->gamemode = a2.gamemode;
		this->field_10 = a2.field_10;
		this->field_14 = a2.field_14;
		return *this;
	}
	LevelSummary& operator =(LevelSummary&& a2) {
		this->worldName = a2.worldName;
		this->field_4 = a2.field_4;
		this->field_8 = a2.field_8;
		this->gamemode = a2.gamemode;
		this->field_10 = a2.field_10;
		this->field_14 = a2.field_14;
		return *this;
	}


	bool operator<(const LevelSummary& a2) const{
		//TODO check is this correct
		return this->field_8 > a2.field_8;
	}
};
