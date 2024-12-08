#include "java.h"
#include <util/logger.h>

JavaVM* vm;
jobject classLoader;
jmethodID mid_findClass;

void setupClassLoader()
{
    jclass c_Thread = Java::Env->FindClass("java/lang/Thread");
    jclass c_Map = Java::Env->FindClass("java/util/Map");
    jclass c_Set = Java::Env->FindClass("java/util/Set");
    jclass c_ClassLoader = Java::Env->FindClass("java/lang/ClassLoader");

    jmethodID mid_getAllStackTraces = Java::Env->GetStaticMethodID(c_Thread, "getAllStackTraces", "()Ljava/util/Map;");
    jmethodID mid_keySet = Java::Env->GetMethodID(c_Map, "keySet", "()Ljava/util/Set;");
    jmethodID mid_toArray = Java::Env->GetMethodID(c_Set, "toArray", "()[Ljava/lang/Object;");
    jmethodID mid_getContextClassLoader = Java::Env->GetMethodID(c_Thread, "getContextClassLoader", "()Ljava/lang/ClassLoader;");
    mid_findClass = Java::Env->GetMethodID(c_ClassLoader, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
    jmethodID mid_currentThread = Java::Env->GetStaticMethodID(c_Thread, "currentThread", "()Ljava/lang/Thread;");

    jobject obj_stackTracesMap = Java::Env->CallStaticObjectMethod(c_Thread, mid_getAllStackTraces);
    jobject obj_threadsSet = Java::Env->CallObjectMethod(obj_stackTracesMap, mid_keySet);

    jobjectArray threads = (jobjectArray)Java::Env->CallObjectMethod(obj_threadsSet, mid_toArray);
    jint szThreads = Java::Env->GetArrayLength(threads);

    for (int i = 0; i < szThreads; i++)
    {
        jobject thread = Java::Env->GetObjectArrayElement(threads, i);
        jobject classLoaderObj = Java::Env->CallObjectMethod(thread, mid_getContextClassLoader);

        if (classLoaderObj) {
            
            jstring className = Java::Env->NewStringUTF("net.minecraft.client.Minecraft");
            jobject minecraftClass = Java::Env->CallObjectMethod(classLoaderObj, mid_findClass, className);

            if (minecraftClass)
            {
                classLoader = classLoaderObj;

                Java::Env->DeleteLocalRef(minecraftClass);

                break;
            }
        }

        Java::Env->DeleteLocalRef(thread);
    }

    Java::Env->DeleteLocalRef(threads);
    Java::Env->DeleteLocalRef(obj_stackTracesMap);
    Java::Env->DeleteLocalRef(obj_threadsSet);
    Java::Env->DeleteLocalRef(c_Thread);
    Java::Env->DeleteLocalRef(c_Map);
    Java::Env->DeleteLocalRef(c_Set);
    Java::Env->DeleteLocalRef(c_ClassLoader);

    Java::Initialized = true;
}

void Java::Init()
{
    Java::Initialized = false;

    // Check if there is any Java VMs in the injected thread
    jsize count;
    if (JNI_GetCreatedJavaVMs(&vm, 1, &count) != JNI_OK || count == 0)
        return;

    jint res = vm->GetEnv((void**)&Java::Env, JNI_VERSION_1_6);
    Logger::Log("Got Java ENV");

    if (res == JNI_EDETACHED)
        res = vm->AttachCurrentThread((void**)&Java::Env, nullptr);
	Logger::Log("Attached to Java VM");

    if (res != JNI_OK)
        return;

    if (Java::Env == nullptr)
        vm->DestroyJavaVM();

    vm->GetEnv((void**)&Java::tiEnv, JVMTI_VERSION);
    setupClassLoader();
	Logger::Log("Java initialized");

    GetMinecraftVersion();
	Logger::Log("Got Minecraft version");
}

void Java::Kill()
{
    vm->DetachCurrentThread();
}

bool Java::AssignClass(std::string name, jclass &out)
{
    jstring className = Java::Env->NewStringUTF(name.c_str());
    jobject findClass = Java::Env->CallObjectMethod(classLoader, mid_findClass, className);

    if (findClass)
    {
        out = (jclass)findClass;
        return true;
    }

	out = Java::Env->FindClass(name.c_str());
	if (out) return true;
        
    return false;
}

jclass Java::findClass(JNIEnv* p_env, jvmtiEnv* p_tienv, const std::string& path)
{
    jint class_count = 0;
    jclass* classes = nullptr;
    jclass foundclass = nullptr;
    p_tienv->GetLoadedClasses(&class_count, &classes);
    for (int i = 0; i < class_count; ++i)
    {
        char* signature_buffer = nullptr;
        p_tienv->GetClassSignature(classes[i], &signature_buffer, nullptr);
        std::string signature = signature_buffer;
        p_tienv->Deallocate((unsigned char*)signature_buffer);
        signature = signature.substr(1);
        signature.pop_back();
        if (signature == path)
        {
            foundclass = (jclass)p_env->NewLocalRef(classes[i]);
        }
        p_env->DeleteLocalRef(classes[i]);
    }
    p_tienv->Deallocate((unsigned char*)classes);
    return foundclass;
}

static bool Is1710()
{
    jclass minecraftClassVanilla1710 = Java::Env->FindClass("bao");
	if (!minecraftClassVanilla1710) return false;

	jfieldID theMinecraftField1710 = Java::Env->GetStaticFieldID(minecraftClassVanilla1710, "M", "Lbao;");
	if (!theMinecraftField1710) return false;

	jobject theMinecraft1710 = Java::Env->GetStaticObjectField(minecraftClassVanilla1710, theMinecraftField1710);
	if (!theMinecraft1710) return false;

	jfieldID launchedVersionField1710 = Java::Env->GetFieldID(minecraftClassVanilla1710, "Z", "Ljava/lang/String;");
	if (!launchedVersionField1710) return false;

	jstring launchedVersion1710 = (jstring)Java::Env->GetObjectField(theMinecraft1710, launchedVersionField1710);
	if (!launchedVersion1710) return false;

	const char* versionCStr1710 = Java::Env->GetStringUTFChars(launchedVersion1710, nullptr);
	std::string version1710 = versionCStr1710;
	Java::Env->ReleaseStringUTFChars(launchedVersion1710, versionCStr1710);

	return version1710 == "1.7.10";
}

static bool Is189()
{
	jclass minecraftClassVanilla189 = Java::Env->FindClass("ave");
	if (!minecraftClassVanilla189) return false;

	jfieldID theMinecraftField189 = Java::Env->GetStaticFieldID(minecraftClassVanilla189, "S", "Lave;");
	if (!theMinecraftField189) return false;

	jobject theMinecraft189 = Java::Env->GetStaticObjectField(minecraftClassVanilla189, theMinecraftField189);
	if (!theMinecraft189) return false;

	jfieldID launchedVersionField189 = Java::Env->GetFieldID(minecraftClassVanilla189, "al", "Ljava/lang/String;");
	if (!launchedVersionField189) return false;

	jstring launchedVersion189 = (jstring)Java::Env->GetObjectField(theMinecraft189, launchedVersionField189);
	if (!launchedVersion189) return false;

	const char* versionCStr189 = Java::Env->GetStringUTFChars(launchedVersion189, nullptr);
	std::string version189 = versionCStr189;
	Java::Env->ReleaseStringUTFChars(launchedVersion189, versionCStr189);

	return version189 == "1.8.9";
}

void Java::GetMinecraftVersion()
{
    /*
=== "Minecraft" class ===
lunar: "net/minecraft/client/Minecraft"
vanilla 1.8.9: "ave"
vanilla 1.7.10: "bao"

=== "theMinecraft" ===
lunar: "theMinecraft", "Lnet/minecraft/client/Minecraft;"
vanilla 1.8.9: "S", "Lave;"
vanilla 1.7.10: "M", "Lbao;"

=== "launchedVersion" ===
lunar: "launchedVersion", "Ljava/lang/String;"
vanilla 1.8.9: "al", "Ljava/lang/String;"
vanilla 1.7.10: "Z", "Ljava/lang/String;"
    */
	jclass minecraftClassLunar;

    if (Java::AssignClass("net.minecraft.client.Minecraft", minecraftClassLunar)) // Lunar Client
    {

        jfieldID theMinecraftField = Java::Env->GetStaticFieldID(minecraftClassLunar, "theMinecraft", "Lnet/minecraft/client/Minecraft;");
        if (!theMinecraftField) { Java::Version = MinecraftVersion::UNKNOWN; return; }

        jobject theMinecraft = Java::Env->GetStaticObjectField(minecraftClassLunar, theMinecraftField);
        if (!theMinecraft) { Java::Version = MinecraftVersion::UNKNOWN; return; }

        jfieldID launchedVersionField = Java::Env->GetFieldID(minecraftClassLunar, "launchedVersion", "Ljava/lang/String;");
        if (!launchedVersionField) { Java::Version = MinecraftVersion::UNKNOWN; return; }

        jstring launchedVersion = (jstring)Java::Env->GetObjectField(theMinecraft, launchedVersionField);
        if (!launchedVersion) { Java::Version = MinecraftVersion::UNKNOWN; return; }

        const char* versionCStr = Java::Env->GetStringUTFChars(launchedVersion, nullptr);
        std::string version = versionCStr;
        Java::Env->ReleaseStringUTFChars(launchedVersion, versionCStr);

        if (version == "1.8.9") { Java::Version = MinecraftVersion::LUNAR_1_8_9; return; }
        else if (version == "1.7.10") { Java::Version = MinecraftVersion::LUNAR_1_7_10; return; }
        else { Java::Version = MinecraftVersion::UNKNOWN; return; }
    }
    else
    {
		if (Is1710()) { Java::Version = MinecraftVersion::VANILLA_1_7_10; return; }
		else if (Is189()) { Java::Version = MinecraftVersion::VANILLA_1_8_9; return; }
		else { Java::Version = MinecraftVersion::UNKNOWN; return; }
    }
}