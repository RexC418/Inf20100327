#pragma once
#ifdef ANDROID
#include <android/AppPlatform_android.hpp>
#include <android/native_activity.h>
struct AppPlatform_android23: AppPlatform_android
{
	AAssetManager* assetManager;
	virtual ~AppPlatform_android23() {
	}
	virtual AssetFile readAssetFile(const std::string& a3){
		if(this->initialized){
			AAsset* v7 = AAssetManager_open(this->assetManager, a3.c_str(), AASSET_MODE_BUFFER);
			if(!v7) return AppPlatform_android::readAssetFile(a3);
			off_t len = AAsset_getLength(v7);
			const void* buf;
			char* v10;
			if(len > 0 && (buf = AAsset_getBuffer(v7)) != 0){
				v10 = new char[len];
				memcpy(v10, buf, len);
			}else{
				len = -1;
				v10 = 0;
			}
			AAsset_close(v7);
			if(v10){
				return AssetFile((uint8_t*) v10, len);
			}
			return AppPlatform_android::readAssetFile(a3);
		}else{
			return AssetFile(0, -1);
		}
	}
	virtual void initWithActivity(ANativeActivity* a2){
		this->field_10C = a2;
		this->assetManager = a2->assetManager;
	}
};
#endif
