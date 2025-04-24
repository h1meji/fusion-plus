#include "EntityLivingBase.h"

#include "java/java.h"
#include "sdk/strayCache.h"

CEntityLivingBase::CEntityLivingBase()
{
	this->clazz = StrayCache::entityLivingBase_class;
}

jclass CEntityLivingBase::GetClass()
{
	return this->clazz;
}

jobject CEntityLivingBase::GetInstance()
{
	return this->instance;
}

float CEntityLivingBase::GetHealth()
{
	return Java::env->CallFloatMethod(this->GetInstance(), StrayCache::entityLivingBase_getHealth);
}

float CEntityLivingBase::GetMaxHealth()
{
	return Java::env->CallFloatMethod(this->GetInstance(), StrayCache::entityLivingBase_getMaxHealth);
}

bool CEntityLivingBase::CanEntityBeSeen(jobject entity) 
{
	return Java::env->CallBooleanMethod(this->GetInstance(), StrayCache::entityLivingBase_canEntityBeSeen, entity);
}