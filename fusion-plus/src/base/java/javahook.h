#pragma once
#include <jni/jni.h>
#include <cstdint>
#include <string>
#include <string>
#include "hotspot/hotspot.h"
#include "java/java.h"

// Source: https://github.com/Lefraudeur/RiptermsGhost/blob/master/Ripterms/Hook/JavaHook.h

struct JavaHook
{
	static void clean();

	typedef void(*i2i_detour_t)(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel);

	class Midi2iHook
	{
	public:
		Midi2iHook(uint8_t* target, i2i_detour_t detour);
		~Midi2iHook();

		bool is_error = true;
	private:
		uint8_t* target = nullptr;
		uint8_t* allocated_assembly = nullptr;
	};

	static bool hook(jmethodID methodID, i2i_detour_t detour);

	template <typename T> static inline void set_return_value(bool* cancel, T return_value)
	{
		*(T*)((void**)cancel + 8) = return_value; //see asm code to understand that
	}

	class JNIFrame
	{
	public:
		JNIFrame(JNIEnv* env = Java::Env, int ref_count = 10);
		~JNIFrame();

		void pop();
		operator bool();
	private:
		JNIEnv* env;
		bool is_success;
	};
};

