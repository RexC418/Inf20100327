#include <util/output/BytesDataOutput.hpp>

void BytesDataOutput::writeString(const std::string& a2) {
	this->writeShort(a2.size() & 0x7fff);
	this->writeBytes(a2.data(), a2.size() & 0x7fff);
}
