#pragma once
#ifdef ANDROID
#include <network/mco/RestRequestJob.hpp>
#include <android/AppPlatform_android.hpp>
#include <mutex>
#include <condition_variable>

struct AndroidRestRequestJob: RestRequestJob
{
	//TODO struct is too big: must be 0x80, seems to be 0x90 - those three fields dont seem to be neccesary
	//but they seem to be set before vt is assigned and not part of std::condition_variable
	int field_54, field_58, field_5C;
	std::condition_variable field_60;
	std::mutex field_64; //maybe waitForAnswerMutex?
	std::mutex mutex;
	int field_6C;
	int httpStatusOrNegativeError;
	std::string content;
	AppPlatform_android* platform;
	bool started;

	AndroidRestRequestJob(Minecraft*);
	bool isRunning();
	void onRequestComplete(int, int, const std::string&);

	virtual ~AndroidRestRequestJob();
	virtual void stop();
	virtual void run();
	virtual void finish();
};
#endif
