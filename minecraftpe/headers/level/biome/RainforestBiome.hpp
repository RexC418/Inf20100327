#pragma once
#include <level/biome/Biome.hpp>
#include <level/gen/feature/TreeFeature.hpp>
#include <util/Random.hpp>

struct RainforestBiome : public Biome{
	RainforestBiome()
		: Biome() {
	}
	virtual ~RainforestBiome() {
	}
	virtual Feature* getTreeFeature(Random* a2){
		a2->genrand_int32(); //very needed to preserve vanilla feature generation
		return new TreeFeature(0, 0);
	}
};
