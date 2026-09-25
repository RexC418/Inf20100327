#pragma once
#include <nbt/Tag.hpp>

struct IDataInput;
struct NbtIo{
	static Tag* read(IDataInput* in){
		Tag* tag;
		tag = Tag::readNamedTag(in);
		if(!tag || tag->getId() != 10) return 0; //XXX wat
		return tag;
	}
};
