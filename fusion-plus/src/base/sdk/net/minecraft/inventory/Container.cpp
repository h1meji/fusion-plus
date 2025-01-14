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
	jfieldID windowIdFieldID = Java::Env->GetFieldID(this->GetClass(), "windowId", "I");
	if (!windowIdFieldID) {
		Logger::Log("windowIdFieldID is null");
		return 0;
	}

	return Java::Env->GetIntField(this->GetInstance(), windowIdFieldID);
}
