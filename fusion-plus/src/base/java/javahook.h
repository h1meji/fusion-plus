#pragma once

#include <cstdint>

#include <string>

#include <jni/jni.h>

#include "hotspot/hotspot.h"
#include "java/java.h"

// Source: https://github.com/Lefraudeur/RiptermsGhost/blob/master/Ripterms/Hook/JavaHook.h
struct JavaHook
{
	static void Shutdown();

	typedef void(*i2i_detour_t)(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel);

	class Midi2iHook
	{
	public:
		Midi2iHook(uint8_t* target, i2i_detour_t detour);
		~Midi2iHook();

		bool m_isError = true;
	private:
		uint8_t* m_target = nullptr;
		uint8_t* m_allocatedAssembly = nullptr;
	};

	static bool Hook(jmethodID methodID, i2i_detour_t detour);

	template <typename T> static inline void SetReturnValue(bool* cancel, T return_value)
	{
		*(T*)((void**)cancel + 8) = return_value; //see asm code to understand that
	}

	class JNIFrame
	{
	public:
		JNIFrame(JNIEnv* env = Java::env, int ref_count = 10);
		~JNIFrame();

		void Pop();
		operator bool();
	private:
		JNIEnv* m_env;
		bool m_isSuccess;
	};
};

