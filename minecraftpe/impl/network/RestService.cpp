#include <network/RestService.hpp>
#include <sstream>

RestService::RestService(const std::string& a2) : serviceURL(a2) {
}
std::map<std::string, std::string> RestService::getCookieData() const{
	return this->cookieData;
}
std::string RestService::getCookieDataAsString() const{
	std::stringstream str;
	for(auto&& data: this->cookieData) {
		//TODO check
		str << data.first << "=" << data.second << ";";
	}
	return str.str();
}
const std::string* RestService::getServiceURL() const{
	return &this->serviceURL;
}
void RestService::setCookieData(const std::string& a2, const std::string& a3) {
	if(a3 == "") {
		this->cookieData[a2] = a3;
	} else {
		this->cookieData.insert({a2, a3}); //TODO check
	}
}
