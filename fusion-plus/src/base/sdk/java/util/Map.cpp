#include "Map.h"

#include "java/java.h"

template class Map<int, int>;
template class Map<std::string, int>;
template class Map<std::string, float>;

template<typename K, typename V>
Map<K, V>::Map(jobject jMap)
{
	this->instance = jMap;
	this->clazz = Java::env->FindClass("java/util/Map");
    entrySetMethod = Java::env->GetMethodID(this->clazz, "entrySet", "()Ljava/util/Set;");
    entrySet = Java::env->CallObjectMethod(jMap, entrySetMethod);

    setClass = Java::env->GetObjectClass(entrySet);
    iteratorMethod = Java::env->GetMethodID(setClass, "iterator", "()Ljava/util/Iterator;");
    iterator = Java::env->CallObjectMethod(entrySet, iteratorMethod);

    iteratorClass = Java::env->GetObjectClass(iterator);
    hasNextMethod = Java::env->GetMethodID(iteratorClass, "hasNext", "()Z");
    nextMethod = Java::env->GetMethodID(iteratorClass, "next", "()Ljava/lang/Object;");
}

template<typename K, typename V>
Map<K, V>::~Map()
{
    Java::env->DeleteLocalRef(this->clazz);
    Java::env->DeleteLocalRef(setClass);
    Java::env->DeleteLocalRef(iteratorClass);
}

template<typename K, typename V>
jclass Map<K, V>::GetClass()
{
    return this->clazz;
}

template<typename K, typename V>
jobject Map<K, V>::GetInstance()
{
    return this->instance;
}

template<typename K, typename V>
std::map<K, V> Map<K, V>::ToMap()
{
    std::map<K, V> cppMap;

    jclass entryClass = nullptr;
    jmethodID getKeyMethod = nullptr;
    jmethodID getValueMethod = nullptr;

    while (Java::env->CallBooleanMethod(iterator, hasNextMethod))
    {
        jobject entry = Java::env->CallObjectMethod(iterator, nextMethod);

        if (!entryClass)
        {
            entryClass = Java::env->GetObjectClass(entry);
            getKeyMethod = Java::env->GetMethodID(entryClass, "getKey", "()Ljava/lang/Object;");
            getValueMethod = Java::env->GetMethodID(entryClass, "getValue", "()Ljava/lang/Object;");
        }

        jobject key = Java::env->CallObjectMethod(entry, getKeyMethod);
        jobject value = Java::env->CallObjectMethod(entry, getValueMethod);

        cppMap[Java::Convert<K>(key)] = Java::Convert<V>(value);

        Java::env->DeleteLocalRef(entry);
        Java::env->DeleteLocalRef(key);
        Java::env->DeleteLocalRef(value);
    }

    if (entryClass) Java::env->DeleteLocalRef(entryClass);

    return cppMap;
}