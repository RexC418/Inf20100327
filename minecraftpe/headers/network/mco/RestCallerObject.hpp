#pragma once
#include <network/mco/RestRequestType.hpp>
#include <network/mco/RestCallerInterup.hpp>

struct RestCallerObject
{
	//TODO inlined in RestCaller::call, size=0x38
	RestCallerInterup interup;
	struct RestCaller* restCaller;
	RestRequestType type;
};
