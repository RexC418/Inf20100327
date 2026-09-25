#pragma once
#include <_types.h>

struct Color4{

	static Color4 WHITE;
	static Color4 GREY;
	static Color4 BLACK;
	static Color4 RED;
	static Color4 GREEN;
	static Color4 BLUE;
	static Color4 NIL;


	float r;
	float g;
	float b;
	float a;

	Color4(float r, float g, float b, float a){
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	int32_t toARGB(void) const {
		int ret;
		//TODO this might break with the wrong endianness?
		((unsigned char*) (&ret))[0] = (unsigned int) ((this->r * 255.0f));
		((unsigned char*) (&ret))[1] = (unsigned int) ((this->g * 255.0f));
		((unsigned char*) (&ret))[2] = (unsigned int) ((this->b * 255.0f));
		((unsigned char*) (&ret))[3] = (unsigned int) ((this->a * 255.0f));
		return ret;
	}
	static Color4 lerp(const Color4& a2, const Color4& a3, float a4){
		return Color4((a4 * a3.r) + ((float)(1.0 - a4) * a2.r), (a4 * a3.g) + ((float)(1.0 - a4) * a2.g), (a4 * a3.b) + ((float)(1.0 - a4) * a2.b), (a4 * a3.a) + ((float)(1.0 - a4) * a2.a));
	}
	static Color4 fromHSB(float, float, float);
	void clamp(void){
		if(this->a > 1.0) this->a = 1.0;
		else if(this->a <= 0.0) this->a = 0.0;

		if(this->r > 1.0) this->r = 1.0;
		else if(this->r <= 0.0) this->r = 0.0;

		if(this->g > 1.0) this->g = 1.0;
		else if(this->g <= 0.0) this->g = 0.0;

		if(this->b > 1.0) this->b = 1.0;
		else if(this->b <= 0.0) this->b = 0.0;
	}
};
