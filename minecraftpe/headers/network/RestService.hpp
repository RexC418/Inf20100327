#pragma once
#include <_types.h>
#include <map>
#include <string>
struct RestService
{
	std::map<std::string, std::string> cookieData;
	const std::string serviceURL;

	RestService(const std::string&);
	std::map<std::string, std::string> getCookieData() const;
	std::string getCookieDataAsString() const;
	const std::string* getServiceURL() const;
	void setCookieData(const std::string&, const std::string&);


};
