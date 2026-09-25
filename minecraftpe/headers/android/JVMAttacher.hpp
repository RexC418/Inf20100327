#ifdef ANDROID
#pragma once
#include <_types.h>
#include <jni.h>
struct JVMAttacher{
    JavaVM* vm;
    JNIEnv* env;
    bool attached;
    //align 9, a, b

	JVMAttacher(JavaVM* vm) {
		this->vm = vm;
		this->env = 0;
		this->attached = 0;
		if (vm->GetEnv((void**) (&this->env), 65540)) {
			vm->AttachCurrentThread(&this->env, 0);
			this->attached = this->env != 0;
		}
	}
	void forceDetach() {
		if (this->attached) {
			this->vm->DetachCurrentThread();
			this->attached = 0;
		}
	}
    ~JVMAttacher(){
    	this->forceDetach();
    }
};
#endif
