#include "java.h"
#include <util/logger.h>

#include "sdk/java/lang/String.h"

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

jclass Java::GetClass(std::string name)
{
    jstring className = Java::Env->NewStringUTF(name.c_str());
    jobject findClass = Java::Env->CallObjectMethod(classLoader, mid_findClass, className);

	if (findClass)
	{
		return (jclass)findClass;
	}

	return Java::Env->FindClass(name.c_str());
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

static bool CheckLunarClient()
{
    jclass minecraftClass;
    Java::AssignClass("net.minecraft.client.Minecraft", minecraftClass);
    if (!minecraftClass) return false;

    jmethodID getMinecraftMethod = Java::Env->GetStaticMethodID(minecraftClass, "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
    if (!getMinecraftMethod) return false;

    jobject theMinecraft = Java::Env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);
    if (!theMinecraft) return false;

    jfieldID launchedVersionField = Java::Env->GetFieldID(minecraftClass, "launchedVersion", "Ljava/lang/String;");
    if (!launchedVersionField) return false;

    jobject launchedVersion = Java::Env->GetObjectField(theMinecraft, launchedVersionField);
    if (!launchedVersion) return false;

    std::string version = String(launchedVersion).ToString();

    if (version == "1.8.9") { Java::Version = MinecraftVersion::LUNAR_1_8_9; return true; }
    else if (version == "1.7.10") { Java::Version = MinecraftVersion::LUNAR_1_7_10; return true; }

    return false;
}

static bool CheckVanilla189()
{
    jclass minecraftClass;
    Java::AssignClass("ave", minecraftClass);
    if (!minecraftClass) return false;

    jmethodID getMinecraftMethod = Java::Env->GetStaticMethodID(minecraftClass, "A", "()Lave;");
    if (!getMinecraftMethod) return false;

    jobject theMinecraft = Java::Env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);
    if (!theMinecraft) return false;

    jfieldID launchedVersionField = Java::Env->GetFieldID(minecraftClass, "al", "Ljava/lang/String;");
    if (!launchedVersionField) return false;

    jobject launchedVersion = Java::Env->GetObjectField(theMinecraft, launchedVersionField);
    if (!launchedVersion) return false;

    std::string version = String(launchedVersion).ToString();

    if (version == "1.8.9") { Java::Version = MinecraftVersion::VANILLA_1_8_9; return true; }

    return false;
}

static bool CheckVanilla1710()
{
    jclass minecraftClass;
    Java::AssignClass("bao", minecraftClass);
    if (!minecraftClass) return false;

    jmethodID getMinecraftMethod = Java::Env->GetStaticMethodID(minecraftClass, "B", "()Lbao;");
    if (!getMinecraftMethod) return false;

    jobject theMinecraft = Java::Env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);
    if (!theMinecraft) return false;

    jfieldID launchedVersionField = Java::Env->GetFieldID(minecraftClass, "Z", "Ljava/lang/String;");
    if (!launchedVersionField) return false;

    jobject launchedVersion = Java::Env->GetObjectField(theMinecraft, launchedVersionField);
    if (!launchedVersion) return false;

    std::string version = String(launchedVersion).ToString();

    if (version == "1.7.10") { Java::Version = MinecraftVersion::VANILLA_1_7_10; return true; }

    return false;
}

static bool CheckForge189()
{
    jclass minecraftClass;
    Java::AssignClass("net.minecraft.client.Minecraft", minecraftClass);
    if (!minecraftClass) return false;

    jmethodID getMinecraftMethod = Java::Env->GetStaticMethodID(minecraftClass, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
    if (!getMinecraftMethod) return false;

    jobject theMinecraft = Java::Env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);
    if (!theMinecraft) return false;

    jfieldID launchedVersionField = Java::Env->GetFieldID(minecraftClass, "field_110447_Z", "Ljava/lang/String;");
    if (!launchedVersionField) return false;

    jobject launchedVersion = Java::Env->GetObjectField(theMinecraft, launchedVersionField);
    if (!launchedVersion) return false;

    std::string version = String(launchedVersion).ToString();

	if (version.find("1.8.9") != std::string::npos) { Java::Version = MinecraftVersion::FORGE_1_8_9; return true; }

    return false;
}

static bool CheckForge1710()
{
    jclass minecraftClass;
    Java::AssignClass("net.minecraft.client.Minecraft", minecraftClass);
    if (!minecraftClass) return false;

    jmethodID getMinecraftMethod = Java::Env->GetStaticMethodID(minecraftClass, "func_71410_x", "()Lnet/minecraft/client/Minecraft;");
    if (!getMinecraftMethod) return false;

    jobject theMinecraft = Java::Env->CallStaticObjectMethod(minecraftClass, getMinecraftMethod);
    if (!theMinecraft) return false;

    jfieldID launchedVersionField = Java::Env->GetFieldID(minecraftClass, "field_110447_Z", "Ljava/lang/String;");
    if (!launchedVersionField) return false;

    jobject launchedVersion = Java::Env->GetObjectField(theMinecraft, launchedVersionField);
    if (!launchedVersion) return false;

    std::string version = String(launchedVersion).ToString();
	Logger::Log("Version: %s", version.c_str());

	if (version.find("1.7.10") != std::string::npos) { Java::Version = MinecraftVersion::FORGE_1_7_10; return true; }

    return false;
}


void Java::GetMinecraftVersion()
{
    if (CheckLunarClient()) return;
    if (CheckVanilla189()) return;
	if (CheckForge189()) return;
	if (CheckVanilla1710()) return;
	if (CheckForge1710()) return;
    
    Java::Version = MinecraftVersion::UNKNOWN;
}