#include <level/gen/InfdevTerrainGenerator.hpp>
#include <algorithm>

InfdevTerrainGenerator::InfdevTerrainGenerator(int64_t seed)
    : random(seed),
      noise1(random, 16),
      noise2(random, 16),
      noise3(random, 8) {
}

double InfdevTerrainGenerator::density(double x, double y, double z) const {
    double densityOffset = y * 4.0 - 64.0;
    if (densityOffset < 0.0)
        densityOffset *= 3.0;

    const double selector = this->noise3.generateNoiseOctaves(
        x * 684.412 / 80.0,
        y * 684.412 / 400.0,
        z * 684.412 / 80.0
    ) / 2.0;

    if (selector < -1.0) {
        double density = this->noise1.generateNoiseOctaves(
            x * 684.412, y * 984.412, z * 684.412
        ) / 512.0 - densityOffset;
        return std::max(-10.0, std::min(10.0, density));
    }

    if (selector > 1.0) {
        double density = this->noise2.generateNoiseOctaves(
            x * 684.412, y * 984.412, z * 684.412
        ) / 512.0 - densityOffset;
        return std::max(-10.0, std::min(10.0, density));
    }

    double low = this->noise1.generateNoiseOctaves(
        x * 684.412, y * 984.412, z * 684.412
    ) / 512.0 - densityOffset;
    double high = this->noise2.generateNoiseOctaves(
        x * 684.412, y * 984.412, z * 684.412
    ) / 512.0 - densityOffset;

    low = std::max(-10.0, std::min(10.0, low));
    high = std::max(-10.0, std::min(10.0, high));
    return low + (high - low) * ((selector + 1.0) / 2.0);
}

void InfdevTerrainGenerator::generateChunk(
    int32_t chunkX,
    int32_t chunkZ,
    uint8_t* blocks,
    uint8_t rockId,
    uint8_t waterId,
    uint8_t grassId,
    uint8_t dirtId
) const {
    // Exact Infdev 20100327 ChunkProviderGenerate.provideChunk() layout:
    // block index = (x << 11) | (z << 7) | y.
    for (int xCell = 0; xCell < 4; ++xCell) {
        for (int zCell = 0; zCell < 4; ++zCell) {
            double noise[33][4];
            const double x = static_cast<double>(chunkX) * 4.0 + xCell;
            const double z = static_cast<double>(chunkZ) * 4.0 + zCell;

            for (int y = 0; y < 33; ++y) {
                noise[y][0] = this->density(x,     y, z);
                noise[y][1] = this->density(x,     y, z + 1.0);
                noise[y][2] = this->density(x + 1.0, y, z);
                noise[y][3] = this->density(x + 1.0, y, z + 1.0);
            }

            for (int yCell = 0; yCell < 32; ++yCell) {
                double n00 = noise[yCell][0];
                double n01 = noise[yCell][1];
                double n10 = noise[yCell][2];
                double n11 = noise[yCell][3];
                const double n00Next = noise[yCell + 1][0];
                const double n01Next = noise[yCell + 1][1];
                const double n10Next = noise[yCell + 1][2];
                const double n11Next = noise[yCell + 1][3];

                for (int yStep = 0; yStep < 4; ++yStep) {
                    const double fy = static_cast<double>(yStep) / 4.0;
                    const double a = n00 + (n00Next - n00) * fy;
                    const double b = n01 + (n01Next - n01) * fy;
                    const double c = n10 + (n10Next - n10) * fy;
                    const double d = n11 + (n11Next - n11) * fy;

                    for (int zStep = 0; zStep < 4; ++zStep) {
                        const double fz = static_cast<double>(zStep) / 4.0;
                        const double e = a + (c - a) * fz;
                        const double g = b + (d - b) * fz;
                        const int blockX = zStep + (xCell << 2);
                        const int blockZ = zCell << 2;
                        int index = (blockX << 11) | (blockZ << 7) | (yCell << 2) | yStep;

                        for (int xStep = 0; xStep < 4; ++xStep) {
                            const double fx = static_cast<double>(xStep) / 4.0;
                            const double value = e + (g - e) * fx;
                            const int blockY = (yCell << 2) + yStep;
                            blocks[index] = value > 0.0 ? rockId : static_cast<uint8_t>(blockY < 64 ? waterId : 0);
                            index += 128;
                        }
                    }
                }
            }
        }
    }

    for (int x = 0; x < 16; ++x) {
        for (int z = 0; z < 16; ++z) {
            int index = (x << 11) | (z << 7) | 127;
            int depth = -1;
            for (int y = 127; y >= 0; --y, --index) {
                if (blocks[index] == 0) {
                    depth = -1;
                } else if (blocks[index] == rockId) {
                    if (depth == -1) {
                        depth = 3;
                        blocks[index] = static_cast<uint8_t>(y >= 63 ? grassId : dirtId);
                    } else if (depth > 0) {
                        --depth;
                        blocks[index] = dirtId;
                    }
                }
            }
        }
    }
}
