#include "EnchantmentHelper.h"

#include "java/java.h"
#include "sdk/strayCache.h"

CEnchantmentHelper::CEnchantmentHelper()
{
	this->clazz = StrayCache::enchantmentHelper_class;
}

jclass CEnchantmentHelper::GetClass()
{
	return this->clazz;
}

jobject CEnchantmentHelper::GetInstance()
{
	return nullptr;
}

std::map<int, int> CEnchantmentHelper::GetEnchantments(CItemStack itemStack)
{
	std::map<int, int> enchantments;

	jobject enchantmentsMap = Java::env->CallStaticObjectMethod(this->GetClass(), StrayCache::enchantmentHelper_getEnchantments, itemStack.GetInstance());
	if (enchantmentsMap == nullptr)
	{
		LOG_ERROR("Failed to get enchantments map");
		return enchantments;
	}

	jclass mapClass = Java::env->FindClass("java/util/Map");
	jclass setClass = Java::env->FindClass("java/util/Set");
	jclass iteratorClass = Java::env->FindClass("java/util/Iterator");
	jclass entryClass = Java::env->FindClass("java/util/Map$Entry");

	if (!mapClass || !setClass || !iteratorClass || !entryClass)
	{
		LOG_ERROR("Failed to get enchantments map");
		return enchantments;
	}

	jmethodID entrySetMethod = Java::env->GetMethodID(mapClass, "entrySet", "()Ljava/util/Set;");
	jobject entrySet = Java::env->CallObjectMethod(enchantmentsMap, entrySetMethod);

	jmethodID iteratorMethod = Java::env->GetMethodID(setClass, "iterator", "()Ljava/util/Iterator;");
	jobject iterator = Java::env->CallObjectMethod(entrySet, iteratorMethod);

	jmethodID hasNextMethod = Java::env->GetMethodID(iteratorClass, "hasNext", "()Z");
	jmethodID nextMethod = Java::env->GetMethodID(iteratorClass, "next", "()Ljava/lang/Object;");
	jmethodID getKeyMethod = Java::env->GetMethodID(entryClass, "getKey", "()Ljava/lang/Object;");
	jmethodID getValueMethod = Java::env->GetMethodID(entryClass, "getValue", "()Ljava/lang/Object;");

	while (Java::env->CallBooleanMethod(iterator, hasNextMethod)) {
		jobject entry = Java::env->CallObjectMethod(iterator, nextMethod);

		jobject keyObject = Java::env->CallObjectMethod(entry, getKeyMethod);
		jobject valueObject = Java::env->CallObjectMethod(entry, getValueMethod);

		jint key = Java::env->CallIntMethod(keyObject, Java::env->GetMethodID(Java::env->FindClass("java/lang/Integer"), "intValue", "()I"));
		jint value = Java::env->CallIntMethod(valueObject, Java::env->GetMethodID(Java::env->FindClass("java/lang/Integer"), "intValue", "()I"));

		enchantments[key] = value;

		Java::env->DeleteLocalRef(entry);
		Java::env->DeleteLocalRef(keyObject);
		Java::env->DeleteLocalRef(valueObject);
	}

	Java::env->DeleteLocalRef(mapClass);
	Java::env->DeleteLocalRef(setClass);
	Java::env->DeleteLocalRef(iteratorClass);
	Java::env->DeleteLocalRef(entryClass);

	return enchantments;
}
