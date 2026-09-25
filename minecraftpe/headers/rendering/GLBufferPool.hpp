#pragma once
#include <_types.h>
#include <set>
#include <deque>
#include <unigl.hpp>

extern struct GLBufferPool glBufferPool;

struct GLBufferPool{
	std::set<uint32_t> usedBuffers;
	std::deque<uint32_t> unusedBuffers;
	int reserveCnt;

	GLBufferPool(unsigned int reserveCnt) {
		this->reserveCnt = reserveCnt;
	} // - not inlined in x86 but inlined in armv7?
	GLuint get(){
		if(this->unusedBuffers.size() < this->reserveCnt) {
			while(this->unusedBuffers.size() < this->reserveCnt) {
				unsigned int bf;
				glGenBuffers(1, &bf);
				if(glGetError()) break;
				this->unusedBuffers.push_back(bf);
			}
		}

		if(this->unusedBuffers.empty()) {
			return 0;
		}

		uint32_t bf = this->unusedBuffers.front();
		this->unusedBuffers.pop_front();
		this->usedBuffers.insert(bf);
		return bf;
	}
	void release(uint32_t n){
		uint32_t v4;
		this->unusedBuffers.push_back(n);
		this->usedBuffers.erase(v4);
	}
	bool_t trim(void){
		//TODO check is correct
		if(this->unusedBuffers.size() == 0){
			return 0;
		}
		while(!this->unusedBuffers.empty()) {
			glDeleteBuffers(1, &this->unusedBuffers.front());
			this->unusedBuffers.pop_front();
		}
		return 1;
	}
	~GLBufferPool(){
		this->trim();
	}
};
