#include "java.h"

#include "util/logger/logger.h"
#include "sdk/java/lang/String.h"

JavaVM* vm;
jobject classLoader;
jmethodID mid_findClass;

static void setupClassLoader()
{
    jclass c_Thread = Java::env->FindClass("java/lang/Thread");
    jclass c_Map = Java::env->FindClass("java/util/Map");
    jclass c_Set = Java::env->FindClass("java/util/Set");
    jclass c_ClassLoader = Java::env->FindClass("java/lang/ClassLoader");

    jmethodID mid_getAllStackTraces = Java::env->GetStaticMethodID(c_Thread, "getAllStackTraces", "()Ljava/util/Map;");
    jmethodID mid_keySet = Java::env->GetMethodID(c_Map, "keySet", "()Ljava/util/Set;");
    jmethodID mid_toArray = Java::env->GetMethodID(c_Set, "toArray", "()[Ljava/lang/Object;");
    jmethodID mid_getContextClassLoader = Java::env->GetMethodID(c_Thread, "getContextClassLoader", "()Ljava/lang/ClassLoader;");
    mid_findClass = Java::env->GetMethodID(c_ClassLoader, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
    jmethodID mid_currentThread = Java::env->GetStaticMethodID(c_Thread, "currentThread", "()Ljava/lang/Thread;");

    jobject obj_stackTracesMap = Java::env->CallStaticObjectMethod(c_Thread, mid_getAllStackTraces);
    jobject obj_threadsSet = Java::env->CallObjectMethod(obj_stackTracesMap, mid_keySet);

    jobjectArray threads = (jobjectArray)Java::env->CallObjectMethod(obj_threadsSet, mid_toArray);
    jint szThreads = Java::env->GetArrayLength(threads);

    for (int i = 0; i < szThreads; i++)
    {
        jobject thread = Java::env->GetObjectArrayElement(threads, i);
        jobject classLoaderObj = Java::env->CallObjectMethod(thread, mid_getContextClassLoader);

        if (classLoaderObj)
        {
            jstring className = Java::env->NewStringUTF("net.minecraft.client.Minecraft");
            jobject minecraftClass = Java::env->CallObjectMethod(classLoaderObj, mid_findClass, className);

            if (minecraftClass)
            {
                classLoader = classLoaderObj;

                Java::env->DeleteLocalRef(minecraftClass);

                break;
            }
        }

        Java::env->DeleteLocalRef(thread);
    }

    Java::env->DeleteLocalRef(threads);
    Java::env->DeleteLocalRef(obj_stackTracesMap);
    Java::env->DeleteLocalRef(obj_threadsSet);
    Java::env->DeleteLocalRef(c_Thread);
    Java::env->DeleteLocalRef(c_Map);
    Java::env->DeleteLocalRef(c_Set);
    Java::env->DeleteLocalRef(c_ClassLoader);

    Java::initialized = true;
}

void Java::Init()
{
    Java::initialized = false;

    // Check if there is any Java VMs in the injected thread
    jsize count;
    if (JNI_GetCreatedJavaVMs(&vm, 1, &count) != JNI_OK || count == 0)
        return;

    jint res = vm->GetEnv((void**)&Java::env, JNI_VERSION_1_6);
    LOG_INFO("Got Java ENV");

    if (res == JNI_EDETACHED)
        res = vm->AttachCurrentThread((void**)&Java::env, nullptr);
	LOG_INFO("Attached to Java VM");

    if (res != JNI_OK)
        return;

    if (Java::env == nullptr)
        vm->DestroyJavaVM();

    vm->GetEnv((void**)&Java::tiEnv, JVMTI_VERSION);
    setupClassLoader();
	LOG_INFO("Java initialized");

    GetMinecraftVersion();
	LOG_INFO("Got Minecraft version");
}

void Java::Shutdown()
{
    vm->DetachCurrentThread();
}

bool Java::AssignClass(std::string name, jclass &out)
{
    jstring className = Java::env->NewStringUTF(name.c_str());
    jobject findClass = Java::env->CallObjectMethod(classLoader, mid_findClass, className);

    if (findClass)
    {
        out = (jclass)findClass;
        return true;
    }

	out = Java::env->FindClass(name.c_str());
	if (out) return true;
        
    return false;
}

jclass Java::GetClass(std::string name)
{
    jstring className = Java::env->NewStringUTF(name.c_str());
    jobject findClass = Java::env->CallObjectMethod(classLoader, mid_findClass, className);

	if (findClass)
	{
		return (jclass)findClass;
	}

	return Java::env->FindClass(name.c_str());
}

jclass Java::FindClass(JNIEnv* env, jvmtiEnv* tienv, const std::string& path)
{
    jint class_count = 0;
    jclass* classes = nullptr;
    jclass foundclass = nullptr;
    tienv->GetLoadedClasses(&class_count, &classes);
    for (int i = 0; i < class_count; ++i)
    {
        char* signature_buffer = nullptr;
        tienv->GetClassSignature(classes[i], &signature_buffer, nullptr);
        std::string signature = signature_buffer;
        tienv->Deallocate((unsigned char*)signature_buffer);
        signature = signature.substr(1);
        signature.pop_back();
        if (signature == path)
        {
            foundclass = (jclass)env->NewLocalRef(classes[i]);
        }
        env->DeleteLocalRef(classes[i]);
    }
    tienv->Deallocate((unsigned char*)classes);
    return foundclass;
}

static bool checkLunarClient
()
{
    jclass minecraftClass;
    Java::AssignClass("net.minecraft.client.Minecraft", minecraftClass);
    if (!minecraftClass) return false;

    jmethodID getMinecraftMethod = Java::env->GetStaticMethodID(minecraftClass, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
    if (!getMinecraftMethod) return false;

    jobject theMinecraft = Java::env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);
    if (!theMinecraft) return false;

    jfieldID launchedVersionField = Java::env->GetFieldID(minecraftClass, "launchedVersion", "Ljava/lang/String;");
    if (!launchedVersionField) return false;

    jobject launchedVersion = Java::env->GetObjectField(theMinecraft, launchedVersionField);
    if (!launchedVersion) return false;

    std::string version = String(launchedVersion).ToString();

    if (version == "1.8.9") { Java::version = MinecraftVersion::LUNAR_1_8_9; return true; }
    else if (version == "1.7.10") { Java::version = MinecraftVersion::LUNAR_1_7_10; return true; }

    return false;
}

static bool CheckVanilla189()
{
    jclass minecraftClass;
    Java::AssignClass("ave", minecraftClass);
    if (!minecraftClass) return false;

    jmethodID getMinecraftMethod = Java::env->GetStaticMethodID(minecraftClass, "A", "()Lave;");
    if (!getMinecraftMethod) return false;

    jobject theMinecraft = Java::env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);
    if (!theMinecraft) return false;

    jfieldID launchedVersionField = Java::env->GetFieldID(minecraftClass, "al", "Ljava/lang/String;");
    if (!launchedVersionField) return false;

    jobject launchedVersion = Java::env->GetObjectField(theMinecraft, launchedVersionField);
    if (!launchedVersion) return false;

    std::string version = String(launchedVersion).ToString();

    if (version == "1.8.9") { Java::version = MinecraftVersion::VANILLA_1_8_9; return true; }

    return false;
}

static bool checkVanilla1710()
{
    jclass minecraftClass;
    Java::AssignClass("bao", minecraftClass);
    if (!minecraftClass) return false;

    jmethodID getMinecraftMethod = Java::env->GetStaticMethodID(minecraftClass, "B", "()Lbao;");
    if (!getMinecraftMethod) return false;

    jobject theMinecraft = Java::env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);
    if (!theMinecraft) return false;

    jfieldID launchedVersionField = Java::env->GetFieldID(minecraftClass, "Z", "Ljava/lang/String;");
    if (!launchedVersionField) return false;

    jobject launchedVersion = Java::env->GetObjectField(theMinecraft, launchedVersionField);
    if (!launchedVersion) return false;

    std::string version = String(launchedVersion).ToString();

    if (version == "1.7.10") { Java::version = MinecraftVersion::VANILLA_1_7_10; return true; }

    return false;
}

static bool checkForge189()
{
    jclass minecraftClass;
    Java::AssignClass("net.minecraft.client.Minecraft", minecraftClass);
    if (!minecraftClass) return false;

    jmethodID getMinecraftMethod = Java::env->GetStaticMethodID(minecraftClass, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
    if (!getMinecraftMethod) return false;

    jobject theMinecraft = Java::env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);
    if (!theMinecraft) return false;

    jfieldID launchedVersionField = Java::env->GetFieldID(minecraftClass, "field_110447_Z", "Ljava/lang/String;");
    if (!launchedVersionField) return false;

    jobject launchedVersion = Java::env->GetObjectField(theMinecraft, launchedVersionField);
    if (!launchedVersion) return false;

    std::string version = String(launchedVersion).ToString();

	if (version.find("1.8.9") != std::string::npos) { Java::version = MinecraftVersion::FORGE_1_8_9; return true; }

    return false;
}

static bool checkForge1710()
{
    jclass minecraftClass;
    Java::AssignClass("net.minecraft.client.Minecraft", minecraftClass);
    if (!minecraftClass) return false;

    jmethodID getMinecraftMethod = Java::env->GetStaticMethodID(minecraftClass, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
    if (!getMinecraftMethod) return false;

    jobject theMinecraft = Java::env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);
    if (!theMinecraft) return false;

    jfieldID launchedVersionField = Java::env->GetFieldID(minecraftClass, "field_110447_Z", "Ljava/lang/String;");
    if (!launchedVersionField) return false;

    jobject launchedVersion = Java::env->GetObjectField(theMinecraft, launchedVersionField);
    if (!launchedVersion) return false;

    std::string version = String(launchedVersion).ToString();
	LOG_INFO("Version: %s", version.c_str());

	if (version.find("1.7.10") != std::string::npos) { Java::version = MinecraftVersion::FORGE_1_7_10; return true; }

    return false;
}


void Java::GetMinecraftVersion()
{
    if (checkLunarClient()) return;
    if (CheckVanilla189()) return;
	if (checkForge189()) return;
	if (checkVanilla1710()) return;
	if (checkForge1710()) return;
    
    Java::version = MinecraftVersion::UNKNOWN;
}