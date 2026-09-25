#pragma once
#include <_types.h>
#include <tile/material/Material.hpp>

struct WebMaterial : Material{
	WebMaterial(void){
		this->alwaysDestroyable = 0;
	}

	virtual bool_t blocksMotion(void) const{
		return 0;
	}
};
