#include <level/storage/RegionFile.hpp>
#include <BitStream.h>
#include <cpputils.hpp>

static int32_t regionFloorDiv32(int32_t v) {
	if(v >= 0) return v / 32;
	return -(((-v) + 31) / 32);
}

static int32_t regionMod32(int32_t v) {
	int32_t r = v % 32;
	if(r < 0) r += 32;
	return r;
}

RegionFile::RegionFile(const std::string& a2) {
	this->fileRaw = 0;
	this->basePath = a2;
	this->path2file.clear();
	this->regionX = 0x7fffffff;
	this->regionZ = 0x7fffffff;
	this->locTable = new int32_t[1024];
	this->bytes4096_2 = new int8_t[4096];
	memset(this->bytes4096_2, 0, 4096);
}

bool_t RegionFile::openForChunk(int32_t chunkX, int32_t chunkZ) {
	int32_t rx = regionFloorDiv32(chunkX);
	int32_t rz = regionFloorDiv32(chunkZ);
	if(this->fileRaw && rx == this->regionX && rz == this->regionZ) return 1;

	this->close();
	this->regionX = rx;
	this->regionZ = rz;
	if(rx == 0 && rz == 0) {
		this->path2file = this->basePath + "/chunks.dat";
	} else {
		std::string regionDir = this->basePath + "/region";
		createFolderIfNotExists(regionDir.c_str());
		this->path2file = regionDir + "/r." + std::to_string(rx) + "." + std::to_string(rz) + ".dat";
	}
	return this->open();
}

void RegionFile::close() {
	if(this->fileRaw) {
		fclose(this->fileRaw);
		this->fileRaw = 0;
	}
}
bool_t RegionFile::open() {
	FILE* file;
	FILE* result;
	int32_t v3, v4, v5, v6, i;
	this->close();
	memset(this->locTable, 0, 4096u);
	file = fopen(this->path2file.c_str(), "r+b");
	this->fileRaw = file;
	if(file) {
		fread(this->locTable, 4u, 1024u, file);
		v3 = 0;
		this->stdMap.clear();
		this->stdMap[0] = 0;
		do {
			v4 = this->locTable[v3];
			if(v4) {
				v5 = v4 >> 8;
				v6 = (uint8_t)v4;
				for(i = 0; i < v6; ++i) this->stdMap[i + v5] = 0;
			}
			++v3;
		} while(v3 != 1024);
	} else {
		result = fopen(this->path2file.c_str(), "w+b");
		this->fileRaw = result;
		if(!result) return 0;
		fwrite(this->locTable, 4u, 1024u, result);
		this->stdMap.clear();
		this->stdMap[0] = 0;
	}
	return this->fileRaw != 0;
}
bool_t RegionFile::readChunk(int32_t chunkX, int32_t chunkZ, RakNet::BitStream** a4) {
	if(!this->openForChunk(chunkX, chunkZ)) return 0;
	int32_t lx = regionMod32(chunkX);
	int32_t lz = regionMod32(chunkZ);
	int32_t result = this->locTable[32 * lz + lx];
	if(result) {
		fseek(this->fileRaw, (result >> 8) << 12, 0);
		int32_t n = 0;
		fread(&n, 4u, 1u, this->fileRaw);
		n -= 4;
		if(n <= 0) return 0;
		uint8_t* v8 = new uint8_t[n];
		fread(v8, 1u, n, this->fileRaw);
		*a4 = new RakNet::BitStream(v8, n, 0);
		return 1;
	}
	return 0;
}
bool_t RegionFile::write(int32_t a2, RakNet::BitStream& a3) {
	fseek(this->fileRaw, a2 << 12, 0);
	int32_t v6 = a3.GetNumberOfBytesUsed() + 4;
	fwrite(&v6, 4u, 1u, this->fileRaw);
	fwrite(a3.GetData(), 1u, a3.GetNumberOfBytesUsed(), this->fileRaw);
	return 1;
}
bool_t RegionFile::writeChunk(int32_t chunkX, int32_t chunkZ, RakNet::BitStream& a4) {
	if(!this->openForChunk(chunkX, chunkZ)) return 0;
	int32_t lx = regionMod32(chunkX);
	int32_t lz = regionMod32(chunkZ);
	int32_t regionIndex = lx + 32 * lz;
	int32_t locTableEntry = this->locTable[regionIndex];
	int32_t v8 = ((int32_t)(a4.GetNumberOfBytesUsed() + 4) >> 12) + 1;
	if(v8 > 256) return 0;
	int32_t firstByteOfLocTableEntry = (uint8_t)locTableEntry;
	int32_t v10 = locTableEntry >> 8;
	int32_t v11 = 0;
	if(v10 && firstByteOfLocTableEntry == v8) {
		this->write(v10, a4);
		return 1;
	}
	int32_t v13 = 1;
	while(v11 < firstByteOfLocTableEntry) {
		this->stdMap[v11 + v10] = v13;
		v13 = v13;
		++v11;
	}
	int32_t v14 = 0, v16 = 0;
	while(true) {
		auto p = this->stdMap.find(v16 + v14);
		if(p == this->stdMap.end()) break;
		if(this->stdMap[v16 + v14]) {
			if(++v14 >= v8) goto LABEL_25;
		} else {
			v16 += v14 + 1;
			v14 = 0;
		}
	}
	{
		int32_t v22 = 0;
		int32_t i = v8 - v14;
		while(v22 < i) {
			fseek(this->fileRaw, 0, 2);
			fwrite(this->bytes4096_2, 4u, 0x400u, this->fileRaw);
			this->stdMap[v22 + v16] = 1;
			++v22;
		}
	}
LABEL_25:
	this->locTable[regionIndex] = v8 | (v16 << 8);
	for(int32_t i = 0; i < v8; ++i) this->stdMap[i + v16] = 0;
	this->write(v16, a4);
	fseek(this->fileRaw, regionIndex * 4, 0);
	fwrite(&this->locTable[regionIndex], 4u, 1u, this->fileRaw);
	return 1;
}

RegionFile::~RegionFile() {
	this->close();
	if(this->locTable) delete[] this->locTable;
	if(this->bytes4096_2) delete[] this->bytes4096_2;
}
