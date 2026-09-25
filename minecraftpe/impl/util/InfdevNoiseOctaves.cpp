#include <util/InfdevNoiseOctaves.hpp>
InfdevNoiseOctaves::InfdevNoiseOctaves(InfdevJavaRandom&r,int n):generators(new InfdevNoisePerlin*[n]),octaves(n){for(int i=0;i<n;++i)generators[i]=new InfdevNoisePerlin(r);}
InfdevNoiseOctaves::~InfdevNoiseOctaves(){for(int i=0;i<octaves;++i)delete generators[i];delete[] generators;}
double InfdevNoiseOctaves::noiseGenerator(double x,double y)const{double out=0.,scale=1.;for(int i=0;i<octaves;++i){out+=generators[i]->generateNoise(x/scale,y/scale)*scale;scale*=2.;}return out;}
double InfdevNoiseOctaves::generateNoiseOctaves(double x,double y,double z)const{double out=0.,scale=1.;for(int i=0;i<octaves;++i){out+=generators[i]->generateNoiseD(x/scale,y/scale,z/scale)*scale;scale*=2.;}return out;}
