#pragma once
#include <nbt/Tag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>

struct StringTag : public Tag{
	std::string value;
	//XXX has 2 vars, and probably uses not std::string
	StringTag(const std::string& name, const std::string& value) : Tag(name), value(value){

	}
	virtual void write(IDataOutput* out) {
		out->writeString(this->value);
	}
	virtual void load(IDataInput* in) {
		this->value = in->readString();
	}
	virtual int32_t getId(void) const {
		return 8;
	}
	virtual std::string toString(void) const {
		return this->value.c_str();
	}
	virtual Tag* copy(void) const {
		return new StringTag(this->getName(), this->value);
	}
	bool_t equals(const Tag& v) const {
		const StringTag* tg = (const StringTag*) (&v);
		bool_t eq = Tag::equals(v);
		if (eq) return this->value == tg->value;

		return eq;
	}
};
