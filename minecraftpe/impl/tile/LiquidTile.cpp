#include <tile/LiquidTile.hpp>
#include <math.h>
#include <math/Vec3.hpp>

void LiquidTile::_trySpreadFire(Level* level, int32_t x, int32_t y, int32_t z, Random* random) {
	int32_t v7; // r8
	int32_t v8; // r9
	int32_t v9; // r10
	Tile* v10; // r3
	int32_t v12; // [sp+4h] [bp-3Ch]

	if(!level->instantTick) {
		static Vec3 vecs[6] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
		v12 = 10;
		while(1) {
			v7 = x + (random->genrand_int32() & 3) - 2;
			v8 = y + (random->genrand_int32() & 3) - 2;
			v9 = z + (random->genrand_int32() & 3) - 2;
			v10 = Tile::tiles[level->getTile(v7, v8, v9)];
			if(v10) {
				if(v10->material->isFlammable()) {
					break;
				}
			}
LABEL_13:
			if(!--v12) {
				return;
			}
		}

		for(Vec3& v: vecs) {
			if(!level->getTile(v.x + v7, v.y + v8, v.z + v9)) {
				level->setTile(v.x + v7, v.y + v8, v.z + v9, Tile::fire->blockID, 3);
				break;
			}
		}
		goto LABEL_13;
	}
}
