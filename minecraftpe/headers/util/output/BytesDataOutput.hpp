#pragma once
#include <util/output/IDataOutput.hpp>

struct BytesDataOutput: IDataOutput
{
	virtual ~BytesDataOutput(){}
	virtual void writeString(const std::string&);
	virtual void writeFloat(float a2) {
		this->writeBytes(&a2, 4);
	}
	virtual void writeDouble(double a2){
		this->writeBytes(&a2, 8);
	}
	virtual void writeByte(char a2) {
		this->writeBytes(&a2, 1);
	}
	virtual void writeShort(int16_t a2) {
		this->writeBytes(&a2, 2);
	}
	virtual void writeInt(int32_t a2) {
		this->writeBytes(&a2, 4);
	}
	virtual void writeLongLong(int64_t a2) {
		this->writeBytes(&a2, 8);
	}
	virtual void writeBytes(const void*, int32_t) = 0;
};
