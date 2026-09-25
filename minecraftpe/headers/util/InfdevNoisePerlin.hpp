#pragma once
#include <util/InfdevJavaRandom.hpp>
struct InfdevNoisePerlin { int permutations[512]; double xCoord,yCoord,zCoord; explicit InfdevNoisePerlin(InfdevJavaRandom&); double generateNoise(double,double) const; double generateNoiseD(double,double,double) const; private: static double fade(double); static double lerp(double,double,double); static double grad(int,double,double,double); double noise3(double,double,double) const; };
