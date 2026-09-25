#pragma once
#include <level/biome/Biome.hpp>
#include <util/Random.hpp>
#include <level/gen/feature/TreeFeature.hpp>
#include <level/gen/feature/BirchFeature.hpp>

struct ForestBiome : public Biome{
	ForestBiome() {
	}

	virtual ~ForestBiome(){}
	virtual Feature* getTreeFeature(Random* a2) {
		if(a2->genrand_int32() % 5) {
			a2->genrand_int32();
			return new TreeFeature(0, 0);
		}
		return new BirchFeature(0);
	}
};
