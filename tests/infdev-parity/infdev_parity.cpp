#include <util/InfdevJavaRandom.hpp>
#include <util/InfdevNoisePerlin.hpp>
#include <util/InfdevNoiseOctaves.hpp>

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

static std::string hex64(uint64_t value) {
    std::ostringstream out;
    out << std::hex << std::setfill('0') << std::setw(16) << value;
    return out.str();
}

static uint64_t bits64(double value) {
    uint64_t bits = 0;
    std::memcpy(&bits, &value, sizeof(bits));
    return bits;
}

static uint32_t bits32(float value) {
    uint32_t bits = 0;
    std::memcpy(&bits, &value, sizeof(bits));
    return bits;
}

static void emitRandom(int64_t seed) {
    InfdevJavaRandom random(seed);

    std::cout << "RNG seed=" << seed << "\n";
    for (int i = 0; i < 32; ++i)
        std::cout << "nextInt." << i << "=" << random.nextInt() << "\n";

    for (int bound : {1, 2, 3, 7, 16, 31, 32, 255, 256, 1024, 65535, 1048576, 2147483647}) {
        random.setSeed(seed);
        std::cout << "nextIntBound." << bound << "=";
        for (int i = 0; i < 32; ++i) {
            if (i) std::cout << ",";
            std::cout << random.nextInt(bound);
        }
        std::cout << "\n";
    }

    random.setSeed(seed);
    for (int i = 0; i < 16; ++i)
        std::cout << "nextLong." << i << "=" << hex64(static_cast<uint64_t>(random.nextLong())) << "\n";

    random.setSeed(seed);
    for (int i = 0; i < 16; ++i)
        std::cout << "nextFloat." << i << "=" << std::hex << std::setfill('0') << std::setw(8) << bits32(random.nextFloat()) << std::dec << "\n";

    random.setSeed(seed);
    for (int i = 0; i < 16; ++i)
        std::cout << "nextDouble." << i << "=" << hex64(bits64(random.nextDouble())) << "\n";
}

static void emitPerlin(int64_t seed) {
    InfdevJavaRandom random(seed);
    InfdevNoisePerlin noise(random);

    static const double samples[][3] = {
        {0.0, 0.0, 0.0},
        {1.25, 2.5, 3.75},
        {-1.25, 2.5, -3.75},
        {12.125, -4.5, 99.75},
        {-1234.5, 0.125, 6789.25},
        {12550824.0, 63.0, -12550824.0}
    };

    std::cout << "PERLIN seed=" << seed << "\n";
    for (size_t i = 0; i < sizeof(samples) / sizeof(samples[0]); ++i) {
        double value = noise.generateNoiseD(samples[i][0], samples[i][1], samples[i][2]);
        std::cout << "sample." << i << "=" << hex64(bits64(value)) << "\n";
    }
}

static void emitOctaves(int64_t seed) {
    InfdevJavaRandom random(seed);
    InfdevNoiseOctaves octaves(random, 8);

    static const double samples[][3] = {
        {0.0, 0.0, 0.0},
        {1.25, 2.5, 3.75},
        {-1.25, 2.5, -3.75},
        {12.125, -4.5, 99.75},
        {-1234.5, 0.125, 6789.25},
        {12550824.0, 63.0, -12550824.0}
    };

    std::cout << "OCTAVES seed=" << seed << " octaves=8\n";
    for (size_t i = 0; i < sizeof(samples) / sizeof(samples[0]); ++i) {
        double value = octaves.generateNoiseOctaves(samples[i][0], samples[i][1], samples[i][2]);
        std::cout << "sample3." << i << "=" << hex64(bits64(value)) << "\n";
    }

    InfdevJavaRandom random2(seed);
    InfdevNoiseOctaves octaves2(random2, 8);
    for (size_t i = 0; i < sizeof(samples) / sizeof(samples[0]); ++i) {
        double value = octaves2.noiseGenerator(samples[i][0], samples[i][1]);
        std::cout << "sample2." << i << "=" << hex64(bits64(value)) << "\n";
    }
}

int main() {
    const int64_t seeds[] = {
        0,
        1,
        -1,
        12345,
        987654321012345678LL,
        std::numeric_limits<int64_t>::min(),
        std::numeric_limits<int64_t>::max()
    };

    for (int64_t seed : seeds) {
        emitRandom(seed);
        emitPerlin(seed);
        emitOctaves(seed);
    }

    return 0;
}
