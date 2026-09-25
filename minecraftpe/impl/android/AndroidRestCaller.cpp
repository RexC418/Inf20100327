#ifdef ANDROID
#include <android/AndroidRestCaller.hpp>
#include <network/mco/MCOConnector.hpp>
#include <Minecraft.hpp>
#include <network/mco/RestCallerObject.hpp>

AndroidRestCaller::AndroidRestCaller(MCOConnector* con, const std::string& s) : RestCaller(con, s){
	this->platform = (AppPlatform_android*) con->minecraft->platform();
}
int AndroidRestCaller::getRequestIndex(int a2, RestCallerObject** a3) {
	printf("AndroidRestCaller::getRequestIndex - not implemented\n");
	return -1;
}
void AndroidRestCaller::onRequestComplete(int a2, int a3, const std::string& a4) {
	RestCallerObject* v24 = 0;
	int reqIndex = this->getRequestIndex(a2, &v24);
	if(reqIndex >= 0){
		printf("AndroidRestCaller::onRequestComplete - not implemented\n");
	}
}

AndroidRestCaller::~AndroidRestCaller() {
	this->requestStop();
}
void AndroidRestCaller::requestStop() {
	this->mutex.lock();
	printf("AndroidRestCaller::requestStop - not implemented\n");
	this->mutex.unlock();
}
void AndroidRestCaller::makeRequest(RestCallerObject* a2) {
	if(a2->interup == 1){
		if(!this->id2request.empty()) return;
	}else if(a2->interup == 0){
		this->requestStop();
	}
	printf("AndroidRestCaller::makeRequest - not implemented\n");
}
#endif
