#pragma once
#include <_types.h>
#include <nbt/Tag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>

struct ByteTag : public Tag{
	int8_t value;

	ByteTag(const std::string& s, int8_t v) : Tag(s){
		this->value = v;
	}

	virtual void write(IDataOutput* out){
		out->writeByte(this->value);
	}
	virtual void load(IDataInput* in){
		this->value = in->readByte();
	}
	virtual int32_t getId(void) const{
		return 1;
	}
	virtual std::string toString() const{
		return std::string((unsigned char) this->value, 1);
	}
	virtual Tag* copy(void) const {
		ByteTag* t = new ByteTag(this->getName(), this->value);
		return t;
	}
	bool_t equals(const Tag& v) const {
		const ByteTag* tg = (const ByteTag*) (&v);
		bool_t eq = Tag::equals(v);
		if (eq) return this->value == tg->value;

		return eq;
	}
};
