#pragma once

#include <map>

#include <jni/jni.h>

#include "sdk/java/IClass.h"

template<typename K, typename V>
struct Map : IClass
{
	Map(jobject jMap);
	~Map();

	jclass GetClass();
	jobject GetInstance();

	std::map<K, V> ToMap();

private:
	jmethodID entrySetMethod;
	jobject entrySet;

	jclass setClass;
	jmethodID iteratorMethod;
	jobject iterator;

	jclass iteratorClass;
	jmethodID hasNextMethod;
	jmethodID nextMethod;
};