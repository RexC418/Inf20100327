#pragma once
#include <level/gen/ChunkSource.hpp>
#include <level/Level.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <level/storage/chunk/ChunkStorage.hpp>

#ifdef ANDROID
#include <android/log.h>
#define INFDEV_CC_LOGI(...) __android_log_print(ANDROID_LOG_INFO, "Inf20100327_CC", __VA_ARGS__)
#else
#define INFDEV_CC_LOGI(...) do { } while (0)
#endif

struct ChunkStorage;
struct LevelChunk;
struct Level;

static bool_t sub_D66664FE(int, int) {
	return 1;
}

struct ChunkCache: ChunkSource
{
	int8_t field_4, field_5, field_6, field_7;
	int32_t lastChunkX, lastChunkZ;
	LevelChunk* emptyChunk;
	ChunkSource* generatorSource;
	ChunkStorage* chunkStorage;
	LevelChunk* chunks[256];
	Level* level;
	LevelChunk* lastChunk;

	virtual ~ChunkCache() {
		// ChunkCache owns the chunks currently stored in its 256 slots.
		// Some old paths can leave the same pointer in more than one slot,
		// so only destroy each LevelChunk once.
		for (int32_t i = 0; i != 256; ++i) {
			LevelChunk* lc = this->chunks[i];
			if (!lc || lc == this->emptyChunk) {
				this->chunks[i] = 0;
				continue;
			}

			bool_t alreadyDeleted = 0;
			for (int32_t j = 0; j < i; ++j) {
				if (this->chunks[j] == lc) {
					alreadyDeleted = 1;
					break;
				}
			}

			if (!alreadyDeleted) {
				lc->deleteBlockData();
				delete lc;
			}

			this->chunks[i] = 0;
		}

		if (this->emptyChunk) {
			delete this->emptyChunk;
			this->emptyChunk = 0;
		}

		if (this->generatorSource) {
			delete this->generatorSource;
			this->generatorSource = 0;
		}
	}
	virtual bool_t hasChunk(int32_t x, int32_t z) {
		LevelChunk* result; // r0
		if (!sub_D66664FE(x, z) || x == this->lastChunkX && z == this->lastChunkZ && this->lastChunk) {
			return 1;
		}
		result = this->chunks[16 * (z & 0xF) + (x & 0xF)];
		if (!result) {
			return 0;
		}
		return result == this->emptyChunk || result->isAt(x, z);
	}
	virtual LevelChunk* getChunk(int32_t x, int32_t z) {
		LevelChunk* result; // r0
		int32_t v7; // r9
		LevelChunk* v9; // r0
		LevelChunk* v10; // r7
		ChunkStorage* chunkStorage; // r0
		ChunkStorage* v12; // r0
		LevelChunk* emptyChunk; // r7
		ChunkSource* generatorSource; // r0
		LevelChunk* v16; // r0
		if (x != this->lastChunkX || z != this->lastChunkZ || (result = this->lastChunk) == 0) {
			if (!sub_D66664FE(x, z)) {
				return this->emptyChunk;
			}
			v7 = (x & 0xF) + 16 * (z & 0xF);
			if (this->hasChunk(x, z)) {
				goto LABEL_48;
			}

			INFDEV_CC_LOGI("MISS x=%d z=%d slot=%d", x, z, v7);
			v9 = this->chunks[v7];
			if (v9) {
				if (v9 != this->emptyChunk) {
					INFDEV_CC_LOGI(
						"EVICT slot=%d old=(%d,%d) new=(%d,%d)",
						v7, v9->chunkX, v9->chunkZ, x, z
					);
				}
				v9->unload();
				v10 = this->chunks[v7];
				if (this->chunkStorage) {
					v10->field_250 = this->level->getTime();
					this->chunkStorage->save(this->level, v10);
				}
				chunkStorage = this->chunkStorage;
				if (chunkStorage) {
					chunkStorage->saveEntities(this->level, this->chunks[v7]);
				}

				// Do not leave lastChunk pointing at memory that is about to
				// be released.
				if (this->lastChunk == v9) {
					this->lastChunk = 0;
				}

				// emptyChunk is shared and must never be deleted here.
				if (v9 != this->emptyChunk) {
					bool_t referencedElsewhere = 0;
					for (int32_t i = 0; i != 256; ++i) {
						if (i != v7 && this->chunks[i] == v9) {
							referencedElsewhere = 1;
							break;
						}
					}

					if (!referencedElsewhere) {
						v9->deleteBlockData();
						delete v9;
					}
				}
				this->chunks[v7] = 0;
			}
			// First try persistent storage. A chunk that has already been
			// generated must come back from storage instead of being regenerated.
			v12 = this->chunkStorage;
			emptyChunk = 0;
			if (v12) {
				emptyChunk = (LevelChunk*) (v12->load(this->level, x, z));
				if (emptyChunk) {
					INFDEV_CC_LOGI(
						"STORAGE x=%d z=%d ptr=%p", x, z, (void*)emptyChunk
					);
					emptyChunk->field_250 = this->level->getTime();
				}
			}

			if (!emptyChunk) {
				// Multiplayer clients receive authoritative chunk data from the
				// server. They must not locally generate/populate a missing chunk,
				// otherwise the client can create different terrain and then
				// overwrite it when the packet arrives.
				if (this->level && this->level->isClientMaybe) {
					emptyChunk = new LevelChunk(this->level, x, z);
					emptyChunk->decorated = 1;
					INFDEV_CC_LOGI(
						"CLIENT_EMPTY x=%d z=%d ptr=%p", x, z, (void*)emptyChunk
					);
				} else if (this->generatorSource) {
					INFDEV_CC_LOGI("GENERATOR x=%d z=%d", x, z);
					emptyChunk = (LevelChunk*) (this->generatorSource->getChunk(x, z));
				} else {
					emptyChunk = this->emptyChunk;
				}
			}
			this->chunks[v7] = emptyChunk; // this->chunks[v7]
			if (emptyChunk) {
				INFDEV_CC_LOGI(
					"INSTALL x=%d z=%d slot=%d ptr=%p",
					x, z, v7, (void*)emptyChunk
				);
			}
			emptyChunk->lightLava();
			v16 = this->chunks[v7];
			if (v16) {
				v16->load();
			}
			// Population is server-side only. A client chunk is populated by
			// the ChunkDataPacket received from the server, not by local
			// noise/feature generation.
			if (!this->level->isClientMaybe &&
				!this->chunks[v7]->decorated &&
				this->hasChunk(x + 1, z + 1) && this->hasChunk(x, z + 1) && this->hasChunk(x + 1, z)) {
				this->postProcess(this, x, z);
			}
			if (this->hasChunk(x - 1, z) && !this->getChunk(x - 1, z)->decorated && this->hasChunk(x - 1, z + 1) && this->hasChunk(x, z + 1) && this->hasChunk(x - 1, z)) {
				this->postProcess(this, x - 1, z);
			}
			if (this->hasChunk(x, z - 1) && !this->getChunk(x, z - 1)->decorated && this->hasChunk(x + 1, z - 1) && this->hasChunk(x, z - 1) && this->hasChunk(x + 1, z)) {
				this->postProcess(this, x, z - 1);
			}
			if (this->hasChunk(x - 1, z - 1) && !this->getChunk(x - 1, z - 1)->decorated && this->hasChunk(x - 1, z - 1) && this->hasChunk(x, z - 1) && this->hasChunk(x - 1, z)) {
				this->postProcess(this, x - 1, z - 1);
			}
			LABEL_48: this->lastChunkX = x;
			this->lastChunkZ = z;
			result = this->chunks[v7];
			this->lastChunk = result;
		}
		return result;
	}
	virtual LevelChunk* create(int32_t x, int32_t z) {
		return this->getChunk(x, z);
	}
	virtual void postProcess(ChunkSource* a2, int32_t x, int32_t z) {
		LevelChunk* v8; // r0
		LevelChunk* v9; // r5
		Level* level; // r2
		bool_t isClientMaybe; // r9
		if (sub_D66664FE(x, z)) {
			v8 = this->getChunk(x, z);
			v9 = v8;
			if (!v8->decorated) {
				INFDEV_CC_LOGI(
					"POSTPROCESS x=%d z=%d ptr=%p", x, z, (void*)v8
				);
				v8->decorated = 1;
				if (this->generatorSource) {
					level = this->level;
					isClientMaybe = level->isClientMaybe;
					level->isClientMaybe = 0;
					this->generatorSource->postProcess(a2, x, z);
					v9->clearUpdateMap();
					this->level->isClientMaybe = isClientMaybe;
				}
			}
		}
	}
	virtual bool_t tick() {
		if (this->chunkStorage) {
			this->chunkStorage->tick();
		}
		return this->generatorSource->tick();
	}
	virtual bool_t shouldSave() {
		return 1;
	}
	virtual void saveAll(bool_t a2) {
		if (this->chunkStorage) {
			std::vector<LevelChunk*> v8;
			for (int32_t i = 0; i != 256; ++i) {
				LevelChunk* chunk = this->chunks[i];
				if (chunk && chunk != this->emptyChunk && (!a2 || chunk->shouldSave(0))) {
					v8.push_back(chunk);
				}
			}
			this->chunkStorage->saveAll(this->level, v8);
		}
	}
	virtual std::vector<Biome::MobSpawnerData> getMobsAt(const MobCategory& a3, int32_t a4, int32_t a5, int32_t a6) {
		return this->generatorSource->getMobsAt(a3, a4, a5, a6);
	}
	virtual std::string gatherStats() {
		return "ChunkCache: 1024";
	}
};
