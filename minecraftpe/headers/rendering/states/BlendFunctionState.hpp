#pragma once
#include <_types.h>
#include <unigl.hpp>

struct BlendFunctionState{
	BlendFunctionState(GLenum sf, GLenum df){
		glBlendFunc(sf, df);
	}
	~BlendFunctionState(){
		glBlendFunc(0x302, 0x303);
	}
};
