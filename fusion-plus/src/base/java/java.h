#pragma once

#include <string>

#include "jni/jni.h"
#include "jni/jvmti.h"

struct Java
{
	static void Init();
	static void Kill();

	static bool AssignClass(std::string name, jclass &out);
	static jclass findClass(JNIEnv* p_env, jvmtiEnv* p_tienv, const std::string& path);

	static inline JNIEnv* Env;
	static inline jvmtiEnv* tiEnv;
	static inline bool Initialized;
};

