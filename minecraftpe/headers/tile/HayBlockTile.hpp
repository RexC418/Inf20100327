#pragma once
#include <tile/RotatedPillarTile.hpp>
#include <tile/material/Material.hpp>

struct HayBlockTile: RotatedPillarTile
{
	TextureUVCoordinateSet field_80, field_98;
	HayBlockTile(int32_t id)
		: RotatedPillarTile(id, Material::dirt) {
		this->field_80 = this->getTextureUVCoordinateSet("hayblock", 0);
		this->field_98 = this->getTextureUVCoordinateSet("hayblock", 1);
	}
	virtual ~HayBlockTile(){}
	virtual TextureUVCoordinateSet* getDirTexture(int32_t a2, int32_t a3) {
		if(a2) {
			return &this->field_98;
		} else {
			return &this->field_80;
		}
	}
};
