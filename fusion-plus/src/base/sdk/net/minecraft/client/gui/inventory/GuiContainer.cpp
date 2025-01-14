#include "GuiContainer.h"

CGuiContainer::CGuiContainer(jobject instance)
{
	this->Instance = instance;
	this->Class = StrayCache::guiContainer_class;
}

jclass CGuiContainer::GetClass()
{
	return this->Class;
}

jobject CGuiContainer::GetInstance()
{
	return this->Instance;
}

CContainer* CGuiContainer::GetContainer()
{
	jobject container = Java::Env->GetObjectField(this->GetInstance(), StrayCache::guiContainer_inventorySlots);
	return new CContainer(container);
}