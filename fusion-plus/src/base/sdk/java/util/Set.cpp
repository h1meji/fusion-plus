#include "Set.h"

#include "java/java.h"

Set::Set(jobject jset)
{
	this->instance = jset;

	this->clazz = Java::env->FindClass("java/util/Set");
	toArrayId = Java::env->GetMethodID(this->clazz, "toArray", "()[Ljava/util/Object;");
}

jclass Set::GetClass()
{
	return this->clazz;
}

jobject Set::GetInstance()
{
	return this->instance;
}

jobjectArray Set::toArray()
{
	return (jobjectArray)Java::env->CallObjectMethod(this->instance, toArrayId);
}
