#pragma once

#include "sdk/java/IClass.h"


struct String : IClass
{
	String(jobject instance);

	String(std::string text);

	jclass GetClass();
	jobject GetInstance();


	std::string ToString();
};

