#pragma once
#include <util/input/IDataInput.hpp>

struct BytesDataInput : IDataInput{
	virtual ~BytesDataInput() {
	}
	virtual std::string readString(void);
	virtual float readFloat(void) {
		float v4;
		this->readBytes(&v4, 4);
		return v4;
	}
	virtual double readDouble(void) {
		double v4;
		this->readBytes(&v4, 8);
		return v4;
	}
	virtual int8_t readByte(void) {
		int8_t v4;
		this->readBytes(&v4, 1);
		return v4;
	}
	virtual int16_t readShort(void) {
		int16_t v4;
		this->readBytes(&v4, 2);
		return v4;
	}
	virtual int32_t readInt(void) {
		int32_t v4;
		this->readBytes(&v4, 4);
		return v4;
	}
	virtual int64_t readLongLong(void) {
		int64_t v4;
		this->readBytes(&v4, 8);
		return v4;
	}
	virtual bool_t readBytes(void*, int32_t) = 0;
	virtual int32_t numBytesLeft(void) = 0;
};
