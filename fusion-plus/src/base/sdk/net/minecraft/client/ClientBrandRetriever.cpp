#include "ClientBrandRetriever.h"

#include "java/java.h"
#include "sdk/java/lang/String.h"
#include "sdk/strayCache.h"

std::string CClientBrandRetriever::GetClientModName()
{
	return String(Java::env->CallStaticObjectMethod(StrayCache::clientBrandRetriever_class, StrayCache::clientBrandRetriever_getClientModName)).ToString();
}
