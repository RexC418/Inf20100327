#pragma once
#include <util/InfdevNoisePerlin.hpp>
struct InfdevNoiseOctaves { InfdevNoisePerlin** generators; int octaves; InfdevNoiseOctaves(InfdevJavaRandom&,int); ~InfdevNoiseOctaves(); double noiseGenerator(double,double)const; double generateNoiseOctaves(double,double,double)const; };
