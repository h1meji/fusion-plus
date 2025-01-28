#include "EnchantmentHelper.h"
#include <java/java.h>
#include <sdk/strayCache.h>

CEnchantMentHelper::CEnchantMentHelper()
{
	this->Class = StrayCache::enchantmentHelper_class;
}

jclass CEnchantMentHelper::GetClass()
{
	return this->Class;
}

jobject CEnchantMentHelper::GetInstance()
{
	return nullptr;
}

std::map<int, int> CEnchantMentHelper::GetEnchantments(CItemStack itemStack)
{
	std::map<int, int> enchantments;

	jclass enchantmentHelper_class;
	Java::AssignClass("net.minecraft.enchantment.EnchantmentHelper", enchantmentHelper_class);
	jmethodID enchantmentHelper_getEnchantments = Java::Env->GetStaticMethodID(enchantmentHelper_class, "getEnchantments", "(Lnet/minecraft/item/ItemStack;)Ljava/util/Map;");

	jobject enchantmentsMap = Java::Env->CallStaticObjectMethod(enchantmentHelper_class, enchantmentHelper_getEnchantments, itemStack.GetInstance());
	if (enchantmentsMap == nullptr)
	{
		Logger::Err("Failed to get enchantments map");
		return enchantments;
	}

	jclass mapClass = Java::Env->FindClass("java/util/Map");
	jclass setClass = Java::Env->FindClass("java/util/Set");
	jclass iteratorClass = Java::Env->FindClass("java/util/Iterator");
	jclass entryClass = Java::Env->FindClass("java/util/Map$Entry");

	if (!mapClass || !setClass || !iteratorClass || !entryClass)
	{
		Logger::Err("Failed to get enchantments map");
		return enchantments;
	}

	jmethodID entrySetMethod = Java::Env->GetMethodID(mapClass, "entrySet", "()Ljava/util/Set;");
	jobject entrySet = Java::Env->CallObjectMethod(enchantmentsMap, entrySetMethod);

	jmethodID iteratorMethod = Java::Env->GetMethodID(setClass, "iterator", "()Ljava/util/Iterator;");
	jobject iterator = Java::Env->CallObjectMethod(entrySet, iteratorMethod);

	jmethodID hasNextMethod = Java::Env->GetMethodID(iteratorClass, "hasNext", "()Z");
	jmethodID nextMethod = Java::Env->GetMethodID(iteratorClass, "next", "()Ljava/lang/Object;");
	jmethodID getKeyMethod = Java::Env->GetMethodID(entryClass, "getKey", "()Ljava/lang/Object;");
	jmethodID getValueMethod = Java::Env->GetMethodID(entryClass, "getValue", "()Ljava/lang/Object;");

	while (Java::Env->CallBooleanMethod(iterator, hasNextMethod)) {
		jobject entry = Java::Env->CallObjectMethod(iterator, nextMethod);

		jobject keyObject = Java::Env->CallObjectMethod(entry, getKeyMethod);
		jobject valueObject = Java::Env->CallObjectMethod(entry, getValueMethod);

		jint key = Java::Env->CallIntMethod(keyObject, Java::Env->GetMethodID(Java::Env->FindClass("java/lang/Integer"), "intValue", "()I"));
		jint value = Java::Env->CallIntMethod(valueObject, Java::Env->GetMethodID(Java::Env->FindClass("java/lang/Integer"), "intValue", "()I"));

		enchantments[key] = value;

		Java::Env->DeleteLocalRef(entry);
		Java::Env->DeleteLocalRef(keyObject);
		Java::Env->DeleteLocalRef(valueObject);
	}

	Java::Env->DeleteLocalRef(mapClass);
	Java::Env->DeleteLocalRef(setClass);
	Java::Env->DeleteLocalRef(iteratorClass);
	Java::Env->DeleteLocalRef(entryClass);

	return enchantments;
}
