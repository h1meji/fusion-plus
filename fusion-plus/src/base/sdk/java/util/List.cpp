#include "List.h"

#include "java/java.h"

List::List(jobject jlist)
{
	this->instance = jlist;

	this->clazz = Java::env->FindClass("java/util/List");
	toArrayId = Java::env->GetMethodID(this->clazz, "toArray", "()[Ljava/lang/Object;");
}

jclass List::GetClass()
{
	return this->clazz;
}

jobject List::GetInstance()
{
	return this->instance;
}

jobjectArray List::toArray()
{
	return (jobjectArray) Java::env->CallObjectMethod(this->GetInstance(), toArrayId);
}
