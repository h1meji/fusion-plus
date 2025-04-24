#include "GuiContainer.h"

CGuiContainer::CGuiContainer(jobject instance)
{
	this->instance = instance;
	this->clazz = StrayCache::guiContainer_class;
}

jclass CGuiContainer::GetClass()
{
	return this->clazz;
}

jobject CGuiContainer::GetInstance()
{
	return this->instance;
}

CContainer* CGuiContainer::GetContainer()
{
	jobject container = Java::env->GetObjectField(this->GetInstance(), StrayCache::guiContainer_inventorySlots);
	return new CContainer(container);
}