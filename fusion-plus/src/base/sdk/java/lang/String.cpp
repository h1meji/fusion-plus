#include "String.h"

#include "java/java.h"

String::String(jobject instance)
{
	this->clazz = Java::env->FindClass("java/lang/String");
	this->instance = instance;
}

String::String(std::string text)
{
	this->clazz = Java::env->FindClass("java/lang/String");
	this->instance = (jobject)Java::env->NewStringUTF(text.c_str());
}

jclass String::GetClass()
{
	return this->clazz;
}

jobject String::GetInstance()
{
	return this->instance;
}

std::string String::ToString()
{
	jstring jStr = (jstring)this->instance;
	const char* nativeStr = Java::env->GetStringUTFChars(jStr, nullptr);
	Java::env->ReleaseStringUTFChars(jStr, nativeStr);
	return std::string(nativeStr);
}
