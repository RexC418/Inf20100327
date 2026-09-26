#pragma once
#include <cstdint>
#include <vector>
#include <util/InfdevJavaRandom.hpp>
#include <util/InfdevNoiseOctaves.hpp>

struct InfdevTerrainGenerator {
    InfdevJavaRandom random;
    InfdevNoiseOctaves noise1;
    InfdevNoiseOctaves noise2;
    InfdevNoiseOctaves noise3;

    explicit InfdevTerrainGenerator(int64_t seed);

    double density(double x, double y, double z) const;

    void generateChunk(
        int32_t chunkX,
        int32_t chunkZ,
        uint8_t* blocks,
        uint8_t rockId = 1,
        uint8_t waterId = 9,
        uint8_t grassId = 2,
        uint8_t dirtId = 3
    ) const;
};
