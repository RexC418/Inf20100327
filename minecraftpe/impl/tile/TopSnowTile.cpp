#include <tile/TopSnowTile.hpp>

TopSnowTile::TopSnowTile(int32_t id, const std::string& name, Material* mat)
	: Tile(id, name, mat) {
	this->setShape(0, 0, 0, 1, 0.125, 1);
	this->setTicking(1);
	this->replaceable = 1;
	this->field_5C = 255;
}
