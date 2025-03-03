#include "RenderManager.h"

#include "java/java.h"
#include "sdk/sdk.h"

CRenderManager::CRenderManager()
{
	this->Class = StrayCache::renderManager_class;
	this->FieldIDs["renderPosX"] = StrayCache::renderManager_renderPosX;
	this->FieldIDs["renderPosY"] = StrayCache::renderManager_renderPosY;
	this->FieldIDs["renderPosZ"] = StrayCache::renderManager_renderPosZ;

	this->FieldIDs["viewerPosX"] = StrayCache::renderManager_viewerPosX;
	this->FieldIDs["viewerPosY"] = StrayCache::renderManager_viewerPosY;
	this->FieldIDs["viewerPosZ"] = StrayCache::renderManager_viewerPosZ;
}

Vector3 CRenderManager::RenderPos()
{
	if (Java::Version == MinecraftVersion::LUNAR_1_8_9 || Java::Version == MinecraftVersion::VANILLA_1_8_9 || Java::Version == MinecraftVersion::FORGE_1_8_9)
	{
		jobject instance = this->GetInstance();
		return Vector3{
			(float)(double)Java::Env->GetDoubleField(instance, this->FieldIDs["renderPosX"]),
			(float)(double)Java::Env->GetDoubleField(instance, this->FieldIDs["renderPosY"]),
			(float)(double)Java::Env->GetDoubleField(instance, this->FieldIDs["renderPosZ"])
		};
	}
	else
	{
		return Vector3{
			(float)(double)Java::Env->GetStaticDoubleField(this->GetClass(), this->FieldIDs["renderPosX"]),
			(float)(double)Java::Env->GetStaticDoubleField(this->GetClass(), this->FieldIDs["renderPosY"]),
			(float)(double)Java::Env->GetStaticDoubleField(this->GetClass(), this->FieldIDs["renderPosZ"])
		};
	}
}

Vector3 CRenderManager::ViewerPos()
{
	jobject instance = this->GetInstance();
	return Vector3{
		(float)(double)Java::Env->GetDoubleField(instance, this->FieldIDs["viewerPosX"]),
		(float)(double)Java::Env->GetDoubleField(instance, this->FieldIDs["viewerPosY"]),
		(float)(double)Java::Env->GetDoubleField(instance, this->FieldIDs["viewerPosZ"])
	};
}

jclass CRenderManager::GetClass()
{
	return this->Class;
}

jobject CRenderManager::GetInstance()
{
	if (Java::Version == MinecraftVersion::LUNAR_1_8_9 || Java::Version == MinecraftVersion::VANILLA_1_8_9 || Java::Version == MinecraftVersion::FORGE_1_8_9)
		return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["renderManager"]);
	else
		return Java::Env->GetStaticObjectField(this->GetClass(), StrayCache::renderManager_instance);
}