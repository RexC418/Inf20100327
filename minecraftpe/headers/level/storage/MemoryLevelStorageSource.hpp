#pragma once
#include <level/storage/LevelStorageSource.hpp>
#include <level/storage/MemoryLevelStorage.hpp>

struct MemoryLevelStorageSource: LevelStorageSource
{
	virtual ~MemoryLevelStorageSource() {
	}
	virtual std::string getName() {
		return "Memory Storage";
	}
	virtual int32_t getDataTagFor(const std::string&) {
		return 0;
	}
	virtual struct LevelStorage* selectLevel(const std::string& a2, bool_t a3) {
		return new MemoryLevelStorage(0);
	}
	virtual bool_t isNewLevelIdAcceptable(const std::string&) {
		return 1;
	}
	virtual void clearAll() {
	}
	virtual void deleteLevel(const std::string&) {
	}
	virtual void renameLevel(const std::string&, const std::string&) {
	}
	virtual bool_t isConvertible(const std::string&) {
		return 0;
	}
	virtual bool_t requiresConversion(const std::string&) {
		return 0;
	}
	virtual bool_t convertLevel(const std::string&, struct ProgressListener*) {
		return 0;
	}
};
