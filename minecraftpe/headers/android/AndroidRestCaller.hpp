#pragma once
#ifdef ANDROID
#include <network/mco/RestCaller.hpp>
#include <util/CMutex.hpp>
#include <vector>

struct AndroidRestCaller: RestCaller
{
	struct AppPlatform_android* platform;
	std::vector<std::pair<int, RestCallerObject*>> id2request;
	CMutex mutex;
	AndroidRestCaller(MCOConnector* con, const std::string& s);
	int getRequestIndex(int, RestCallerObject**);
	void onRequestComplete(int, int, const std::string&);

	virtual ~AndroidRestCaller();
	virtual void requestStop();
	virtual void makeRequest(RestCallerObject*);
};
#endif
