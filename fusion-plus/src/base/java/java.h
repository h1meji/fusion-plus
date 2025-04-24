#pragma once

#include <string>

#include <jni/jni.h>
#include <jni/jvmti.h>

enum MinecraftVersion
{
	LUNAR_1_8_9,
	VANILLA_1_8_9,
	FORGE_1_8_9,
	LUNAR_1_7_10,
	VANILLA_1_7_10,
	FORGE_1_7_10,
	UNKNOWN
};

struct Java
{
	static void Init();
	static void Shutdown();

	static bool AssignClass(std::string name, jclass &out);
	static jclass GetClass(std::string name);
	static jclass FindClass(JNIEnv* env, jvmtiEnv* tienv, const std::string& path);

	static void GetMinecraftVersion();

	static inline JNIEnv* env;
	static inline jvmtiEnv* tiEnv;
	static inline bool initialized;
	static inline MinecraftVersion version;
};

