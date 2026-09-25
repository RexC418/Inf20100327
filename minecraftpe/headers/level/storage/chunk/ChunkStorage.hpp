#pragma once
#include <_types.h>
#include <vector>
struct Level;
struct LevelChunk;

struct ChunkStorage{
	virtual ~ChunkStorage() {
	}
	virtual struct LevelChunk* load(Level*, int32_t, int32_t) {
		return 0;
	}
	virtual void save(Level*, LevelChunk*) {
	}
	virtual void saveEntities(Level*, LevelChunk*) {
	}
	virtual void saveAll(Level* a2, std::vector<LevelChunk*>& a3) {
		for (int32_t i = 0; i < a3.size(); ++i) {
			this->save(a2, a3[i]);
		}
	}
	virtual void tick() {
	}
	virtual void flush() {
	}
};
