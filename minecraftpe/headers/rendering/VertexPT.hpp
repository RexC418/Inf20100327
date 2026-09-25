#pragma once
#include <_types.h>
#include <math/Vec3.hpp>
struct VertexPT{
	Vec3 vec;
	float u, v;

	VertexPT(){
		this->u = 0;
		this->v = 0;
	}
	VertexPT(const VertexPT &vv, float u, float v){
		this->vec.x = 0;
		this->vec.y = 0;
		this->vec.z = 0;

		this->u = u;
		this->v = v;
		this->vec.x = vv.vec.x;
		this->vec.y = vv.vec.y;
		this->vec.z = vv.vec.z;
	}
};
