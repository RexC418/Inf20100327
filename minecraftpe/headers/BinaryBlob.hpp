#pragma once
#include <_types.h>

struct BinaryBlob
{
	char* data;
	int length;

	BinaryBlob(char* d, int sz) {
		this->data = d;
		this->length = sz;
	}
};
