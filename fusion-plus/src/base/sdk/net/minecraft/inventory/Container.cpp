#include "Container.h"

CContainer::CContainer(jobject instance)
{
	this->instance = instance;
	this->clazz = Java::env->GetObjectClass(instance);
}

jclass CContainer::GetClass()
{
	return this->clazz;
}

jobject CContainer::GetInstance()
{
	return this->instance;
}

int CContainer::GetWindowId()
{
	jfieldID windowIdFieldID = Java::env->GetFieldID(this->GetClass(), StrayCache::container_windowId_name, "I");

	if (!windowIdFieldID)
	{
		return -1;
	}

	return Java::env->GetIntField(this->GetInstance(), windowIdFieldID);
}
