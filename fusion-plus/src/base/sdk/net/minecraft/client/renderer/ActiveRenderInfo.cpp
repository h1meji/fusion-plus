#include "ActiveRenderInfo.h"

#include "java/java.h"
#include "sdk/sdk.h"
#include "sdk/java/nio/FloatBuffer.h"
#include "util/logger/logger.h"

CActiveRenderInfo::CActiveRenderInfo()
{
	this->clazz = StrayCache::activeRenderInfo_class;
}

jclass CActiveRenderInfo::GetClass()
{
	return this->clazz;
}

jobject CActiveRenderInfo::GetInstance()
{
	return nullptr;
}

Matrix CActiveRenderInfo::ProjectionMatrix()
{
	jobject projection = Java::env->GetStaticObjectField(this->GetClass(), StrayCache::activeRenderInfo_PROJECTION);
	Matrix m = FloatBuffer::FloatBuffer(projection).GetMatrix();
	Java::env->DeleteLocalRef(projection);
	return m;
}

Matrix CActiveRenderInfo::ModelViewMatrix()
{
	jobject modelView = Java::env->GetStaticObjectField(this->GetClass(), StrayCache::activeRenderInfo_MODELVIEW);
	Matrix m = FloatBuffer::FloatBuffer(modelView).GetMatrix();
	Java::env->DeleteLocalRef(modelView);
	return m;
}

