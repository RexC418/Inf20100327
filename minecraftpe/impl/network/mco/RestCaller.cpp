#include <network/mco/RestCaller.hpp>
#include <util/CMutex.hpp>

RestCaller::RestCaller(MCOConnector*, const std::string&) {
	printf("RestCaller::RestCaller - not implemented\n");
}
void RestCaller::addToCookieData(std::string&, const std::string&, const std::string&) {
	printf("RestCaller::addToCookieData - not implemented\n");
}
void RestCaller::call(RestCallerType, RestCallerInterup, const char_t*, const char_t*, void (MCOConnector::*)(int32_t, std::string, const RestCallTagData&), void (MCOConnector::*)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData&, int32_t) {
	printf("RestCaller::call - not implemented\n");
}
RestCaller* RestCaller::create(MCOConnector*, const std::string&) {
	printf("RestCaller::create - not implemented\n");
	return 0;
}
void RestCaller::del(RestCallerInterup, const char_t*, void (MCOConnector::*)(int32_t, std::string, const RestCallTagData&), void (MCOConnector::*)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData&, int32_t) {
	printf("RestCaller::del - not implemented\n");
}
void RestCaller::get(RestCallerInterup, const char_t*, void (MCOConnector::*)(int32_t, std::string, RestCallTagData const&), void (MCOConnector::*)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData&, int32_t) {
	printf("RestCaller::get - not implemented\n");
}
std::string RestCaller::getCookieData() {
	printf("RestCaller::getCookieData - not implemented\n");
	return "";
}
void RestCaller::globalCleanUp(){
	printf("RestCaller::globalCleanUp - not implemented\n");
}
void RestCaller::globalInit(){
	printf("RestCaller::globalInit - not implemented\n");
}
void RestCaller::post(RestCallerInterup, const char_t*, const char_t*, void (MCOConnector::*)(int32_t, std::string, const RestCallTagData&), void (MCOConnector::*)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData&, int32_t){
	printf("RestCaller::post - not implemented\n");
}
void RestCaller::put(RestCallerInterup, const char_t*, const char_t*, void (MCOConnector::*)(int32_t, std::string, const RestCallTagData&), void (MCOConnector::*)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData&, int32_t){
	printf("RestCaller::put - not implemented\n");
}
void RestCaller::setKey(const std::string&){
	printf("RestCaller::setKey - not implemented\n");
}
void RestCaller::setSidAndUser(const std::string&, const std::string&){
	printf("RestCaller::setSidAndUser - not implemented\n");
}

RestCaller::~RestCaller() {
	printf("RestCaller::~RestCaller - not implemented\n");
}
void RestCaller::urlEscape(const std::string&) {
	printf("RestCaller::urlEscape - not implemented\n");
}
