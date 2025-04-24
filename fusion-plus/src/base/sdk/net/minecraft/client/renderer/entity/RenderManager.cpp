#include "RenderManager.h"

#include "java/java.h"
#include "sdk/sdk.h"

CRenderManager::CRenderManager()
{
	this->clazz = StrayCache::renderManager_class;
}

Vector3 CRenderManager::RenderPos()
{
	if (Java::version == MinecraftVersion::LUNAR_1_8_9 || Java::version == MinecraftVersion::VANILLA_1_8_9 || Java::version == MinecraftVersion::FORGE_1_8_9)
	{
		jobject instance = this->GetInstance();
		return Vector3{
			(float)(double)Java::env->GetDoubleField(instance, StrayCache::renderManager_renderPosX),
			(float)(double)Java::env->GetDoubleField(instance, StrayCache::renderManager_renderPosY),
			(float)(double)Java::env->GetDoubleField(instance, StrayCache::renderManager_renderPosZ)
		};
	}
	else
	{
		return Vector3{
			(float)(double)Java::env->GetStaticDoubleField(this->GetClass(), StrayCache::renderManager_renderPosX),
			(float)(double)Java::env->GetStaticDoubleField(this->GetClass(), StrayCache::renderManager_renderPosY),
			(float)(double)Java::env->GetStaticDoubleField(this->GetClass(), StrayCache::renderManager_renderPosZ)
		};
	}
}

Vector3 CRenderManager::ViewerPos()
{
	jobject instance = this->GetInstance();
	return Vector3{
		(float)(double)Java::env->GetDoubleField(instance, StrayCache::renderManager_viewerPosX),
		(float)(double)Java::env->GetDoubleField(instance, StrayCache::renderManager_viewerPosY),
		(float)(double)Java::env->GetDoubleField(instance, StrayCache::renderManager_viewerPosZ)
	};
}

jclass CRenderManager::GetClass()
{
	return this->clazz;
}

jobject CRenderManager::GetInstance()
{
	if (Java::version == MinecraftVersion::LUNAR_1_8_9 || Java::version == MinecraftVersion::VANILLA_1_8_9 || Java::version == MinecraftVersion::FORGE_1_8_9)
	{
		return Java::env->GetObjectField(SDK::minecraft->GetInstance(), StrayCache::minecraft_renderManager);
	}
	else
	{
		return Java::env->GetStaticObjectField(this->GetClass(), StrayCache::renderManager_instance);
	}
}