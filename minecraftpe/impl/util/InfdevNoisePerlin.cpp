#include <util/InfdevNoisePerlin.hpp>
#include <cmath>
#include <cstdint>

// Match the original Infdev helper that computes an integer floor from a double.
// It first performs Java's narrowing conversion (including saturation), then
// decrements for negative fractional values. The decrement intentionally wraps
// like a Java int when the saturated value is Integer.MIN_VALUE.
static int32_t javaDoubleToInt(double value) {
    if (std::isnan(value)) return 0;
    if (value >= 2147483647.0) return INT32_MAX;
    if (value <= -2147483648.0) return INT32_MIN;
    return static_cast<int32_t>(value);
}

static int32_t javaFloorToInt(double value) {
    int32_t truncated = javaDoubleToInt(value);
    if (value < static_cast<double>(truncated)) {
        uint32_t wrapped = static_cast<uint32_t>(truncated);
        --wrapped;
        return static_cast<int32_t>(wrapped);
    }
    return truncated;
}
InfdevNoisePerlin::InfdevNoisePerlin(InfdevJavaRandom&r){xCoord=r.nextDouble()*256.;yCoord=r.nextDouble()*256.;zCoord=r.nextDouble()*256.;for(int i=0;i<256;++i)permutations[i]=i;for(int i=0;i<256;++i){int j=r.nextInt(256-i)+i,t=permutations[i];permutations[i]=permutations[j];permutations[j]=t;permutations[i+256]=permutations[i];}}
double InfdevNoisePerlin::fade(double x){return x*x*x*(x*(x*6.-15.)+10.);}
double InfdevNoisePerlin::lerp(double x,double a,double b){return a+x*(b-a);}
double InfdevNoisePerlin::grad(int h,double x,double y,double z){h&=15;double u=h<8?x:y,v=h<4?y:((h!=12&&h!=14)?z:x);return ((h&1)==0?u:-u)+((h&2)==0?v:-v);}
double InfdevNoisePerlin::noise3(double x,double y,double z)const{double xx=x+xCoord,yy=y+yCoord,zz=z+zCoord;int floorX=javaFloorToInt(xx),floorY=javaFloorToInt(yy),floorZ=javaFloorToInt(zz);double fx=xx-static_cast<double>(floorX),fy=yy-static_cast<double>(floorY),fz=zz-static_cast<double>(floorZ);int X=floorX&255,Y=floorY&255,Z=floorZ&255;double u=fade(fx),v=fade(fy),w=fade(fz);int A=permutations[X]+Y,AA=permutations[A]+Z,AB=permutations[A+1]+Z,B=permutations[X+1]+Y,BA=permutations[B]+Z,BB=permutations[B+1]+Z;double a=lerp(u,grad(permutations[AA],fx,fy,fz),grad(permutations[BA],fx-1,fy,fz)),b=lerp(u,grad(permutations[AB],fx,fy-1,fz),grad(permutations[BB],fx-1,fy-1,fz));double c=lerp(u,grad(permutations[AA+1],fx,fy,fz-1),grad(permutations[BA+1],fx-1,fy,fz-1)),d=lerp(u,grad(permutations[AB+1],fx,fy-1,fz-1),grad(permutations[BB+1],fx-1,fy-1,fz-1));return lerp(w,lerp(v,a,b),lerp(v,c,d));}
double InfdevNoisePerlin::generateNoise(double x,double y)const{return noise3(x,y,0.);}
double InfdevNoisePerlin::generateNoiseD(double x,double y,double z)const{return noise3(x,y,z);}
