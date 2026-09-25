#pragma once
#include <util/input/BytesDataInput.hpp>
#include <BitStream.h>

struct RakDataInput: BytesDataInput
{
	RakNet::BitStream* stream;

	virtual bool_t readBytes(void* a2, int32_t a3) {
		if (this->hasBytesLeft(a3)) {
			this->stream->ReadBits((unsigned char*) (a2), 8 * a3, 1);
			return 1;
		}
		return 0;
	}
	virtual int32_t numBytesLeft(void) {
		//XXX might be not as in 0.8.1
		return this->stream->GetNumberOfUnreadBits() >> 3;
	}
};
