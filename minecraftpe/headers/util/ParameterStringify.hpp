#pragma once
#include <_types.h>
#include <vector>
#include <string>
#include <sstream>

struct ParameterStringify
{

	static inline void stringifyNext(std::vector<std::string>& a1) {}

	template<typename T, typename... _args>
	static void stringifyNext(std::vector<std::string>& a1, T t, _args... args) {
		std::stringstream s;
		s << t;
		a1.emplace_back(s.str());
		ParameterStringify::stringifyNext(a1, args...);
	}
};


