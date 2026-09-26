#include <util/InfdevJavaRandom.hpp>
#include <util/InfdevNoisePerlin.hpp>
#include <util/InfdevNoiseOctaves.hpp>

#include <cstdint>
#include <cstring>
#include <fstream>
#include <vector>
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



static const int TERRAIN_CHUNKS[][2]={{0,0},{1,0},{-1,0},{0,-1},{-1,-1},{37,-91},{-1024,2048}};
static const double TERRAIN_SAMPLES[][3]={{0.0,0.0,0.0},{1.25,2.5,3.75},{-1.25,2.5,-3.75},{12.125,-4.5,99.75},{-1234.5,0.125,6789.25},{12550824.0,63.0,-12550824.0}};

static void writeU32BE(std::ofstream& out,uint32_t v){
    out.put(static_cast<char>((v>>24)&255));out.put(static_cast<char>((v>>16)&255));
    out.put(static_cast<char>((v>>8)&255));out.put(static_cast<char>(v&255));
}
static void writeI64BE(std::ofstream& out,int64_t v){
    const uint64_t u=static_cast<uint64_t>(v);
    for(int sh=56;sh>=0;sh-=8) out.put(static_cast<char>((u>>sh)&255));
}
static void writeDoubleBE(std::ofstream& out,double v){
    const uint64_t u=bits64(v);
    for(int sh=56;sh>=0;sh-=8) out.put(static_cast<char>((u>>sh)&255));
}

struct InfdevTerrainParity {
    InfdevJavaRandom random;
    InfdevNoiseOctaves noise1,noise2,noise3;
    explicit InfdevTerrainParity(int64_t seed)
        :random(seed),noise1(random,16),noise2(random,16),noise3(random,8){}
    double density(double x,double y,double z) const{
        double offset=y*4.0-64.0;
        if(offset<0.0) offset*=3.0;
        const double selector=noise3.generateNoiseOctaves(x*684.412/80.0,y*684.412/400.0,z*684.412/80.0)/2.0;
        if(selector<-1.0){
            double d=noise1.generateNoiseOctaves(x*684.412,y*984.412,z*684.412)/512.0-offset;
            return std::max(-10.0,std::min(10.0,d));
        }
        if(selector>1.0){
            double d=noise2.generateNoiseOctaves(x*684.412,y*984.412,z*684.412)/512.0-offset;
            return std::max(-10.0,std::min(10.0,d));
        }
        double low=noise1.generateNoiseOctaves(x*684.412,y*984.412,z*684.412)/512.0-offset;
        double high=noise2.generateNoiseOctaves(x*684.412,y*984.412,z*684.412)/512.0-offset;
        low=std::max(-10.0,std::min(10.0,low));
        high=std::max(-10.0,std::min(10.0,high));
        return low+(high-low)*((selector+1.0)/2.0);
    }
    void chunk(int32_t cx,int32_t cz,std::vector<uint8_t>& blocks) const{
        blocks.assign(32768,0);
        for(int xc=0;xc<4;++xc)for(int zc=0;zc<4;++zc){
            double n[33][4];
            const double x=static_cast<double>(cx)*4.0+xc;
            const double z=static_cast<double>(cz)*4.0+zc;
            for(int y=0;y<33;++y){
                n[y][0]=density(x,y,z);n[y][1]=density(x,y,z+1.0);
                n[y][2]=density(x+1.0,y,z);n[y][3]=density(x+1.0,y,z+1.0);
            }
            for(int yc=0;yc<32;++yc){
                const double n00=n[yc][0],n01=n[yc][1],n10=n[yc][2],n11=n[yc][3];
                const double p00=n[yc+1][0],p01=n[yc+1][1],p10=n[yc+1][2],p11=n[yc+1][3];
                for(int ys=0;ys<4;++ys){
                    const double fy=static_cast<double>(ys)/4.0;
                    const double a=n00+(p00-n00)*fy,b=n01+(p01-n01)*fy,c=n10+(p10-n10)*fy,d=n11+(p11-n11)*fy;
                    for(int zs=0;zs<4;++zs){
                        const double fz=static_cast<double>(zs)/4.0;
                        const double e=a+(c-a)*fz,g=b+(d-b)*fz;
                        const int bx=zs+(xc<<2),bz=zc<<2;
                        int index=(bx<<11)|(bz<<7)|(yc<<2)|ys;
                        for(int xs=0;xs<4;++xs){
                            const double fx=static_cast<double>(xs)/4.0;
                            const double value=e+(g-e)*fx;
                            const int by=(yc<<2)+ys;
                            blocks[index]=value>0.0?1:static_cast<uint8_t>(by<64?9:0);
                            index+=128;
                        }
                    }
                }
            }
        }
        for(int x=0;x<16;++x)for(int z=0;z<16;++z){
            int index=(x<<11)|(z<<7)|127,depth=-1;
            for(int y=127;y>=0;--y,--index){
                if(blocks[index]==0) depth=-1;
                else if(blocks[index]==1){
                    if(depth==-1){depth=3;blocks[index]=static_cast<uint8_t>(y>=63?2:3);}
                    else if(depth>0){--depth;blocks[index]=3;}
                }
            }
        }
    }
};

int main(int argc,char** argv) {
    const int64_t seeds[] = {
        0,1,-1,12345,987654321012345678LL,
        std::numeric_limits<int64_t>::min(),std::numeric_limits<int64_t>::max()
    };

    const char* path=argc>1?argv[1]:"tests/infdev-parity/cpp.bin";
    std::ofstream out(path,std::ios::binary);
    if(!out){std::cerr<<"Failed to open "<<path<<"\n";return 2;}
    writeU32BE(out,0x49464431);
    writeU32BE(out,static_cast<uint32_t>(sizeof(seeds)/sizeof(seeds[0])));

    for(int64_t seed:seeds){
        emitRandom(seed);
        emitPerlin(seed);
        emitOctaves(seed);

        InfdevTerrainParity provider(seed);
        std::cout<<"TERRAIN_DENSITY seed="<<seed<<"\n";
        for(size_t i=0;i<sizeof(TERRAIN_SAMPLES)/sizeof(TERRAIN_SAMPLES[0]);++i)
            std::cout<<"sample."<<i<<"="<<hex64(bits64(provider.density(TERRAIN_SAMPLES[i][0],TERRAIN_SAMPLES[i][1],TERRAIN_SAMPLES[i][2])))<<"\n";

        std::cout<<"TERRAIN_DENSITY_GRID seed="<<seed<<"\n";
        writeI64BE(out,seed);
        for(const auto& c:TERRAIN_CHUNKS){
            writeU32BE(out,static_cast<uint32_t>(c[0]));writeU32BE(out,static_cast<uint32_t>(c[1]));
            for(int xc=0;xc<4;++xc)for(int zc=0;zc<4;++zc)for(int y=0;y<33;++y){
                const double x=static_cast<double>(c[0])*4.0+xc;
                const double z=static_cast<double>(c[1])*4.0+zc;
                writeDoubleBE(out,provider.density(x,y,z));
                writeDoubleBE(out,provider.density(x,y,z+1.0));
                writeDoubleBE(out,provider.density(x+1.0,y,z));
                writeDoubleBE(out,provider.density(x+1.0,y,z+1.0));
            }
        }

        std::cout<<"TERRAIN_CHUNK seed="<<seed<<"\n";
        writeI64BE(out,seed);
        for(const auto& c:TERRAIN_CHUNKS){
            std::vector<uint8_t> blocks;
            provider.chunk(c[0],c[1],blocks);
            std::cout<<"chunk."<<c[0]<<"."<<c[1]<<".size="<<blocks.size()<<"\n";
            std::cout<<"chunk."<<c[0]<<"."<<c[1]<<".fnv64="<<hex64(fnv1a(blocks.data(),blocks.size()))<<"\n";
            writeU32BE(out,static_cast<uint32_t>(c[0]));writeU32BE(out,static_cast<uint32_t>(c[1]));
            writeU32BE(out,static_cast<uint32_t>(blocks.size()));
            out.write(reinterpret_cast<const char*>(blocks.data()),static_cast<std::streamsize>(blocks.size()));
        }
        std::cout<<"TERRAIN_DONE seed="<<seed<<"\n";
    }
    out.close();
    return 0;
}
