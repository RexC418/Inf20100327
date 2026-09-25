#include <util/Color4.hpp>
#include <math.h>

Color4 Color4::WHITE(1.0, 1.0, 1.0, 1.0);
Color4 Color4::GREY(0.5, 0.5, 0.5, 1.0);
Color4 Color4::BLACK(0.0, 0.0, 0.0, 1.0);
Color4 Color4::RED(1.0, 0.0, 0.0, 1.0);
Color4 Color4::GREEN(0.0, 1.0, 0.0, 1.0);
Color4 Color4::BLUE(0.0, 0.0, 1.0, 1.0);
Color4 Color4::NIL(0.0, 0.0, 0.0, 0.0);

Color4 Color4::fromHSB(float h, float s, float b){
	float v7, v8, v9, v10, v11, g, v13, a;

	if(s != 0.0){
		v7 = (float)(h - floorf(h)) * 6.0;
		v8 = floorf(v7);
		v9 = b * (float)(1.0 - (float)(s * (float)(v7 - v8)));
		v10 = b * (float)(1.0 - s);
		v11 = b * (float)(1.0 - (float)(s * (float)(1.0 - (float)(v7 - v8))));
		switch((int32_t)v7){
			case 0:
				return Color4(b, v11, v10, 1.0f);
			case 1:
				return Color4(v9, b, v10, 1.0f);
			case 2:
				return Color4(v10, b, v11, 1.0f);
			case 3:
				return Color4(v10, v9, b, 1.0f);
			case 4:
				return Color4(v11, v10, b, 1.0f);
			case 5:
				return Color4(b, v10, v9, 1.0f);
			default:
				return Color4::NIL;
		}
	}
	return Color4(b, b, b, 1.0f);
}
