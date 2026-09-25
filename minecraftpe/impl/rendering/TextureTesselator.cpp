#include <rendering/TextureTesselator.hpp>

TextureTesselator::TextureTesselator(TextureData* td, int32_t txmin, int32_t tymin, int32_t txmax, int32_t tymax, Vec3 f10, Color4 f1C, Color4 f2C)
	: field_1C(Color4::BLACK)
	, field_2C(Color4::WHITE) {
	this->texXMin = txmin;
	this->texYMin = tymin;
	this->texXMax = txmax;
	this->texYMax = tymax;
	this->textureData = td;
	this->field_10 = f10;
	this->field_1C = f1C;
	this->field_2C = f2C;
}
