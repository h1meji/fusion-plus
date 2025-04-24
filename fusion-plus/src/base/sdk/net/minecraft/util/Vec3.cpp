#include "Vec3.h"

#include "java/java.h"
#include "util/logger.h"
#include "sdk/strayCache.h"

CVec3::CVec3()
{
	this->clazz = StrayCache::movingObjectPosition_class;
}

CVec3::CVec3(jobject instance) : CVec3()
{
	this->instance = instance;
}

jclass CVec3::GetClass()
{
	return this->clazz;
}

jobject CVec3::GetInstance()
{
	return this->instance;
}

Vector3 CVec3::GetNativeVector3()
{
	float x = (float)Java::env->GetDoubleField(this->GetInstance(), StrayCache::vec3_xCoord);
	float y = (float)Java::env->GetDoubleField(this->GetInstance(), StrayCache::vec3_yCoord);
	float z = (float)Java::env->GetDoubleField(this->GetInstance(), StrayCache::vec3_zCoord);
	return Vector3{
		x,y,z
	};
}