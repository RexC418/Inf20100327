#include <util/InfdevJavaRandom.hpp>
void InfdevJavaRandom::setSeed(int64_t v){seed=(static_cast<uint64_t>(v)^MULTIPLIER)&MASK;}
int32_t InfdevJavaRandom::next(int32_t bits){seed=(seed*MULTIPLIER+ADDEND)&MASK;return static_cast<int32_t>(seed>>(48-bits));}
int32_t InfdevJavaRandom::nextInt(){return next(32);}
int32_t InfdevJavaRandom::nextInt(int32_t bound){if(bound<=0)return 0;if((bound&-bound)==bound)return static_cast<int32_t>((bound*static_cast<int64_t>(next(31)))>>31);int32_t bits,value;do{bits=next(31);value=bits%bound;}while(bits-value+(bound-1)<0);return value;}
int64_t InfdevJavaRandom::nextLong(){const uint64_t hi=static_cast<uint64_t>(static_cast<int64_t>(next(32)))<<32;const int64_t lo=static_cast<int64_t>(next(32));return static_cast<int64_t>(hi+static_cast<uint64_t>(lo));}
float InfdevJavaRandom::nextFloat(){return next(24)/16777216.0f;}
double InfdevJavaRandom::nextDouble(){uint64_t a=static_cast<uint32_t>(next(26)),b=static_cast<uint32_t>(next(27));return static_cast<double>((a<<27)+b)/9007199254740992.0;}
