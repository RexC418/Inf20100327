#pragma once
#include <pthread.h>

//TODO check
struct Mutex{
	pthread_mutex_t mutex;

	Mutex() {
		pthread_mutex_init(&this->mutex, 0);
	}
	~Mutex() {
		pthread_mutex_destroy(&this->mutex);
	}
};
