#pragma once

#include <_types.h>
#include <string>

struct KeyMapping{
	std::string name;
	int32_t keyCode;

	KeyMapping() {
		this->keyCode = 0;
	}
	~KeyMapping() {
	}
	KeyMapping(const std::string& name, int32_t code) :
			name(name) {
		this->keyCode = code;
	}
	void operator =(KeyMapping&& key) {
		this->name = key.name;
		this->keyCode = key.keyCode;
	}
};
