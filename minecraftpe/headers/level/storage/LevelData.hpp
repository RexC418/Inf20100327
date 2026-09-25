#pragma once
#include <_types.h>
#include <string>
#include <vector>
#include <RakNetTypes.h>
#include <entity/player/PlayerData.hpp>
#include <cstdint>


struct LevelData{
	PlayerData playerData;
	int32_t field_2C, field_30, field_34, field_38;
	int32_t field_3C, field_40, field_44, field_48;
	int32_t field_4C, field_50;
	std::string levelName;
	int32_t seedLow, seedHigh;
	int32_t xSpawn, ySpawn, zSpawn;
	long time;
	int32_t lastPlayed;
	long sizeOnDisk;
	struct CompoundTag* playerTag;
	int32_t dimensionID;
	int32_t gameType;
	int32_t storageVersion;
	bool_t spawnMobs;
	char align1, align2, align3;
	int32_t stopTime;
	int32_t generatorVersion;

	LevelData(struct CompoundTag*);
	LevelData(const LevelData&);
	LevelData(const struct LevelSettings&, const std::string&, int32_t);
	LevelData(void);
	struct CompoundTag* createTag(const std::vector<struct Player*>&);
	struct CompoundTag* createTag();
	int32_t getDimension();
	int32_t getGameType() const;
	int32_t getGeneratorVersion() const;
	int32_t getLastPlayed() const;
	std::string getLevelName();
	struct CompoundTag* getLoadedPlayerTag();
	int64_t getSeed() const;
	int32_t getSizeOnDisk() const;
	bool_t getSpawnMobs() const;
	int32_t getStorageVersion() const;
	void getTagData(const struct CompoundTag*);
	int32_t getTime() const;
	int32_t getXSpawn() const;
	int32_t getYSpawn() const;
	int32_t getZSpawn() const;
	LevelData& operator=(const LevelData&);
	void setDimension(int32_t);
	void setGameType(int32_t);
	void setGeneratorVersion(int32_t);
	void setLevelName(const std::string&);
	void setLoadedPlayerTag(struct CompoundTag*);
	void setLoadedPlayerTo(struct Player*);
	void setPlayerTag(struct CompoundTag*);
	void setSeed(int64_t);
	void setSizeOnDisk(long);
	void setSpawn(int32_t, int32_t, int32_t);
	void setSpawnMobs(bool_t);
	void setStopTime(long);
	void setStorageVersion(int32_t);
	void setTagData(struct CompoundTag*, struct CompoundTag*);
	void setTime(long);
	void setXSpawn(int32_t);
	void setYSpawn(int32_t);
	void setZSpawn(int32_t);
	void v1_read(RakNet::BitStream&, int32_t);
	void v1_write(RakNet::BitStream&);
	~LevelData();
};
