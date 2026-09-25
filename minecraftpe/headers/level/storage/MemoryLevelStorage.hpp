#pragma once
#include <level/storage/LevelStorage.hpp>
#include <level/storage/chunk/MemoryChunkStorage.hpp>


struct MemoryLevelStorage: LevelStorage
{
	ChunkStorage* chunkStorage;


	MemoryLevelStorage(ChunkStorage* a2) {
		this->chunkStorage = a2;
	}
	virtual ~MemoryLevelStorage() {
		if(this->chunkStorage) delete this->chunkStorage;
	}
	virtual LevelData* prepareLevel(Level*) {
		return 0;
	}
	virtual ChunkStorage* createChunkStorage(Dimension* a2) {
		this->chunkStorage = new MemoryChunkStorage();
		return this->chunkStorage;
	}
	virtual void saveLevelData(LevelData&, std::vector<Player*>*) {
	}
	virtual void closeAll(){}

};
