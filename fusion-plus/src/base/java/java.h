#pragma once

#include <string>

#include "jni/jni.h"
#include "jni/jvmti.h"

enum MinecraftVersion
{
	LUNAR_1_8_9,
	LUNAR_1_7_10,
	VANILLA_1_8_9,
	VANILLA_1_7_10,
	UNKNOWN
};

struct Java
{
	static void Init();
	static void Kill();

	static bool AssignClass(std::string name, jclass &out);
	static jclass findClass(JNIEnv* p_env, jvmtiEnv* p_tienv, const std::string& path);

	static void GetMinecraftVersion();

	static inline JNIEnv* Env;
	static inline jvmtiEnv* tiEnv;
	static inline bool Initialized;
	static inline MinecraftVersion Version;
};

