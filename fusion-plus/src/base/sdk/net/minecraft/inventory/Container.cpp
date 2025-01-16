#include "Container.h"

CContainer::CContainer(jobject instance)
{
	this->Instance = instance;
	this->Class = Java::Env->GetObjectClass(instance);
}

jclass CContainer::GetClass()
{
	return this->Class;
}

jobject CContainer::GetInstance()
{
	return this->Instance;
}

int CContainer::GetWindowId()
{
	jfieldID windowIdFieldID = Java::Env->GetFieldID(this->GetClass(), StrayCache::container_windowId_name, "I");
	if (!windowIdFieldID) {
		return -1;
	}

	return Java::Env->GetIntField(this->GetInstance(), windowIdFieldID);
}
