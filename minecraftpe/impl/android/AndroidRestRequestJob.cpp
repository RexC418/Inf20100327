#ifdef ANDROID
#include <android/AndroidRestRequestJob.hpp>
#include <Minecraft.hpp>
AndroidRestRequestJob::AndroidRestRequestJob(Minecraft* a2){
	this->started = 0;
	this->platform = (AppPlatform_android*) a2->platform();
}
bool AndroidRestRequestJob::isRunning(){
	DEBUGMSG("AndroidRestRequestJob::isRunning - not implemented\n");
	return 0;
}
void AndroidRestRequestJob::onRequestComplete(int, int, const std::string&){
	DEBUGMSG("AndroidRestRequestJob::onRequestComplete - not implemented\n");
}

AndroidRestRequestJob::~AndroidRestRequestJob(){
	DEBUGMSG("AndroidRestRequestJob::~AndroidRestRequestJob - not implemented\n");
}
void AndroidRestRequestJob::stop(){
	DEBUGMSG("AndroidRestRequestJob::stop - not implemented\n");
}
void AndroidRestRequestJob::run(){
	DEBUGMSG("AndroidRestRequestJob::run - not implemented\n");
}
void AndroidRestRequestJob::finish(){
	DEBUGMSG("AndroidRestRequestJob::finish - not implemented\n");
}
#endif
