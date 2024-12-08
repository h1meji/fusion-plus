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
	jobject instance = this->GetInstance();
	return Vector3{
		(float)(double) Java::Env->GetDoubleField(instance, this->FieldIDs["renderPosX"]),
		(float)(double) Java::Env->GetDoubleField(instance, this->FieldIDs["renderPosY"]),
		(float)(double) Java::Env->GetDoubleField(instance, this->FieldIDs["renderPosZ"])
	};
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
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["renderManager"]);
}