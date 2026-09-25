#include <util/input/BytesDataInput.hpp>

std::string BytesDataInput::readString() {
	int slen = this->readShort();
	int v6;

	if(slen > 0) {
		if(slen == 0x7fff) v6 = 32766;
		else v6 = slen;
		char* v7 = new char[v6+1];
		this->readBytes(v7, v6);
		v7[v6] = 0;
		std::string ret(v7);
		if(v7) delete[] v7;
		return ret;
	}

	return "";
}
