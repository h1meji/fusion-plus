#include "AxisAlignedBB.h"

#include "java/java.h"
#include "util/logger.h"
#include "sdk/strayCache.h"

CAxisAlignedBB::CAxisAlignedBB()
{
	this->clazz = StrayCache::axisAlignedBB_class;
}

CAxisAlignedBB::CAxisAlignedBB(jobject instance) : CAxisAlignedBB()
{
	this->instance = instance;
}

jclass CAxisAlignedBB::GetClass()
{
	return this->clazz;
}

jobject CAxisAlignedBB::GetInstance()
{
	return this->instance;
}

BoundingBox CAxisAlignedBB::GetNativeBoundingBox()
{
	return BoundingBox{
		Java::env->GetDoubleField(this->GetInstance(), StrayCache::axisAlignedBB_minX),
		Java::env->GetDoubleField(this->GetInstance(), StrayCache::axisAlignedBB_minY),
		Java::env->GetDoubleField(this->GetInstance(), StrayCache::axisAlignedBB_minZ),

		Java::env->GetDoubleField(this->GetInstance(), StrayCache::axisAlignedBB_maxX),
		Java::env->GetDoubleField(this->GetInstance(), StrayCache::axisAlignedBB_maxY),
		Java::env->GetDoubleField(this->GetInstance(), StrayCache::axisAlignedBB_maxZ),
	};
}

void CAxisAlignedBB::SetBoundingBox(BoundingBox newBoundingBox)
{
	Java::env->SetDoubleField(this->GetInstance(), StrayCache::axisAlignedBB_minX, newBoundingBox.minX);
	Java::env->SetDoubleField(this->GetInstance(), StrayCache::axisAlignedBB_minY, newBoundingBox.minY);
	Java::env->SetDoubleField(this->GetInstance(), StrayCache::axisAlignedBB_minZ, newBoundingBox.minZ);

	Java::env->SetDoubleField(this->GetInstance(), StrayCache::axisAlignedBB_maxX, newBoundingBox.maxX);
	Java::env->SetDoubleField(this->GetInstance(), StrayCache::axisAlignedBB_maxY, newBoundingBox.maxY);
	Java::env->SetDoubleField(this->GetInstance(), StrayCache::axisAlignedBB_maxZ, newBoundingBox.maxZ);
}
