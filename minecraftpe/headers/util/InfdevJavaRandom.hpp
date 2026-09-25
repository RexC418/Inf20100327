#pragma once
#include <cstdint>
struct InfdevJavaRandom { static const uint64_t MULTIPLIER=0x5DEECE66DULL, ADDEND=0xBULL, MASK=(1ULL<<48)-1; uint64_t seed; explicit InfdevJavaRandom(int64_t s=0):seed(0){setSeed(s);} void setSeed(int64_t); int32_t next(int32_t); int32_t nextInt(); int32_t nextInt(int32_t); int64_t nextLong(); float nextFloat(); double nextDouble(); };
