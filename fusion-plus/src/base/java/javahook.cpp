#include "javahook.h"

#include <vector>

#include <Windows.h>

#include "java/java.h"
#include "util/logger.h"

// Source: https://github.com/Lefraudeur/RiptermsGhost/blob/master/Ripterms/Hook/JavaHook.cpp

static constexpr int NO_COMPILE = HotSpot::JVM_ACC_NOT_C2_COMPILABLE | HotSpot::JVM_ACC_NOT_C1_COMPILABLE | HotSpot::JVM_ACC_NOT_C2_OSR_COMPILABLE | HotSpot::JVM_ACC_QUEUED;

struct i2iHookData
{
    void* _i2i_entry = nullptr;
    JavaHook::Midi2iHook* hook = nullptr;
};
static std::vector<i2iHookData> hooked_i2i_entries{};
struct HookedMethod
{
    HotSpot::Method* method = nullptr;
    JavaHook::i2i_detour_t detour = nullptr;
};
static std::vector<HookedMethod> hooked_methods{};

static void* findCorrectHookPlace(void* _i2i_entry)
{
    uint8_t pattern[] =
    {
        0x89, 0x84, 0x24, 0x90, 0x90, 0x90, 0x90,
        0x89, 0x84, 0x24, 0x90, 0x90, 0x90, 0x90,
        0x89, 0x84, 0x24, 0x90, 0x90, 0x90, 0x90,
        0x89, 0x84, 0x24, 0x90, 0x90, 0x90, 0x90,
        0x41, 0xC6, 0x87, 0x90, 0x90, 0x90, 0x90, 0x00
    };

    uint8_t pattern2[] =
    {
        0x4C, 0x8B, 0x75, 0x90, 0xC3
    };

    uint8_t* curr = (uint8_t*)_i2i_entry;
    while (curr < (uint8_t*)_i2i_entry + 0x400)
    {
        int matches = 0;
        for (int i = 0; i < sizeof(pattern); ++i)
        {
            if (pattern[i] == 0x90 || pattern[i] == curr[i])
                matches++;
            else
                break;
        }
        if (matches == sizeof(pattern))
        {
            for (uint8_t* curr2 = curr; curr2 > curr - 100; --curr2)
            {
                int matches2 = 0;
                for (int j = 0; j < sizeof(pattern2); ++j)
                {
                    if (pattern2[j] == 0x90 || pattern2[j] == curr2[j])
                        matches2++;
                    else
                        break;
                }
                if (matches2 == sizeof(pattern2))
                    HotSpot::frame::localsOffset = *(char*)(curr2 + 3);

            }
            return curr + sizeof(pattern) - 8;
        }
        curr += 1;
    }

    //8: sizeof : mov    BYTE PTR [r15+_do_not_unlock_if_synchronized_offset],0x0
    //we place the hook here because enough size and correct time
    return nullptr;
}

static void commonDetour(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel)
{
    if (!(*(void**)thread->GetEnv()) || thread->GetThreadState() != HotSpot::_thread_in_Java || !Java::env) return;
    for (HookedMethod& hk : hooked_methods)
    {
        if (hk.method == frame->GetMethod())
        {
            hk.detour(frame, thread, cancel);
            thread->SetThreadState(HotSpot::_thread_in_Java);
            return;
        }
    }
}

static uint8_t* allocateNearbyMemory(uint8_t* nearby_addr, int size, int access)
{
    for (int i = 65536;
        i < 0x7FFFFFFF;
        i += 65536)
    {
        uint8_t* allocated = (uint8_t*)VirtualAlloc(nearby_addr + i, size, MEM_COMMIT | MEM_RESERVE, access);
        if (allocated)
            return allocated;
        allocated = (uint8_t*)VirtualAlloc(nearby_addr - i, size, MEM_COMMIT | MEM_RESERVE, access);
        if (allocated)
            return allocated;
    }
    return nullptr;
}

void JavaHook::Shutdown()
{
    for (i2iHookData& hk : hooked_i2i_entries)
    {
        delete hk.hook;
    }
    for (HookedMethod& hm : hooked_methods)
    {
        hm.method->SetDontInline(false);
        int* flags = (int*)hm.method->GetAccessFlags();
        *flags &= ~(NO_COMPILE);
    }
}

bool JavaHook::Hook(jmethodID methodID, i2i_detour_t detour)
{
    static int runonce = []()->int
        {
            jvmtiCapabilities capabilities{ .can_retransform_classes = JVMTI_ENABLE };
            Java::tiEnv->AddCapabilities(&capabilities);
            return 0;
        }();
    if (!methodID || !detour)
        return false;

    HotSpot::Method* method = *(HotSpot::Method**)methodID;
    for (HookedMethod& hk : hooked_methods)
    {
        if (hk.method == method)
            return true;
    }


    method->SetDontInline(true);
    int* flags = (int*)method->GetAccessFlags();
    *flags |= (NO_COMPILE);

    jclass owner = nullptr;
    Java::tiEnv->GetMethodDeclaringClass(methodID, &owner);
    Java::tiEnv->RetransformClasses(1, &owner); //small trick to delete any already compiled / inlined code
    Java::env->DeleteLocalRef(owner);

    method = *(HotSpot::Method**)methodID;

    method->SetDontInline(true);
    flags = (int*)method->GetAccessFlags();
    *flags |= (NO_COMPILE);


    hooked_methods.push_back({ method, detour });

    bool hook_new_i2i = true;
    void* i2i = method->GetI2iEntry();
    for (i2iHookData& hk : hooked_i2i_entries)
    {
        if (hk._i2i_entry == i2i)
            hook_new_i2i = false;
    }


    if (!hook_new_i2i) return true;

    uint8_t* target = (uint8_t*)findCorrectHookPlace(i2i);
    if (!target)
    {
        LOG_ERROR("Failed to find correct i2i hook location");
        LOG_ERROR("Debug: i2ientry: %p", i2i);
        return false;
    }
    LOG_INFO("placed i2i hook at: %p", (void*)target);
    Midi2iHook* hook = new Midi2iHook(target, commonDetour);
    if (!hook)
        return false;

    hooked_i2i_entries.push_back({ i2i, hook });
    return true;
}

JavaHook::Midi2iHook::Midi2iHook(uint8_t* target, i2i_detour_t detour) :
    m_target(target)
{
    constexpr int HOOK_SIZE = 8;
    constexpr int JMP_SIZE = 5;
    constexpr int JE_OFFSET = 0x3d;
    constexpr int JE_SIZE = 6;
    constexpr int DETOUR_ADDRESS_OFFSET = 0x56;
    /*
push   rax
push   rcx
push   rdx
push   r8
push   r9
push   r10
push   r11
push   rbp
push   0x0
mov    rcx,rbp
mov    rdx,r15
lea    r8,[rsp]
mov    rbp,rsp
and    rsp,0xfffffffffffffff0
sub    rsp,0x20
call   [rip+data]
mov    rsp,rbp
pop    rax
cmp    rax,0x0
pop    rbp
pop    r11
pop    r10
pop    r9
pop    r8
pop    rdx
pop    rcx
pop    rax
je     0x11111111
movq   xmm0,rax
mov    rbx,QWORD PTR [rbp-0x8]
mov    rsp,rbp
pop    rbp
pop    rsi
mov    rsp,rbx
jmp    rsi
data:
    */
    uint8_t assembly[] =
    {
        0x50, 0x51, 0x52, 0x41, 0x50, 0x41, 0x51, 0x41, 0x52, 0x41, 0x53, 0x55, 0x6A, 0x00, 0x48, 0x89, 0xE9, 0x4C, 0x89, 0xFA, 0x4C, 0x8D, 0x04,
        0x24, 0x48, 0x89, 0xE5, 0x48, 0x83, 0xE4, 0xF0, 0x48, 0x83, 0xEC, 0x20, 0xFF, 0x15, 0x2D, 0x00, 0x00, 0x00, 0x48, 0x89, 0xEC, 0x58, 0x48,
        0x83, 0xF8, 0x00, 0x5D, 0x41, 0x5B, 0x41, 0x5A, 0x41, 0x59, 0x41, 0x58, 0x5A, 0x59, 0x58, 0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x66, 0x48,
        0x0F, 0x6E, 0xC0, 0x48, 0x8B, 0x5D, 0xF8, 0x48, 0x89, 0xEC, 0x5D, 0x5E, 0x48, 0x89, 0xDC, 0xFF, 0xE6,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 //detour address
    };

    m_allocatedAssembly = allocateNearbyMemory(target, HOOK_SIZE + sizeof(assembly), PAGE_EXECUTE_READWRITE);
    if (!m_allocatedAssembly)
    {
        LOG_ERROR("Failed to allocate memory for i2i hook");
        return;
    }
    int32_t jmp_back_delta = (int32_t)(target + HOOK_SIZE - (m_allocatedAssembly + HOOK_SIZE + JE_OFFSET + JE_SIZE));
    *(int32_t*)(assembly + JE_OFFSET + 2) = jmp_back_delta;

    *(i2i_detour_t*)(assembly + DETOUR_ADDRESS_OFFSET) = detour;

    memcpy(m_allocatedAssembly, target, HOOK_SIZE);
    memcpy(m_allocatedAssembly + HOOK_SIZE, assembly, sizeof(assembly));

    DWORD original_prot = 0;
    VirtualProtect(m_allocatedAssembly, HOOK_SIZE + sizeof(assembly), PAGE_EXECUTE_READ, &original_prot);

    VirtualProtect(target, JMP_SIZE, PAGE_EXECUTE_READWRITE, &original_prot);
    target[0] = 0xE9U;
    int32_t jmp_detour_delta = (int32_t)(m_allocatedAssembly - (target + JMP_SIZE));
    *(int32_t*)(target + 1) = jmp_detour_delta;
    VirtualProtect(target, JMP_SIZE, original_prot, &original_prot);

    m_isError = false;
}

JavaHook::Midi2iHook::~Midi2iHook()
{
    if (m_isError)
        return;

    DWORD original = 0;
    if (m_target[0] == 0xE9U && VirtualProtect(m_target, 5, PAGE_EXECUTE_READWRITE, &original))
    {
        memcpy(m_target, m_allocatedAssembly, 5);
        VirtualProtect(m_target, 5, original, &original);
    }

    VirtualFree(m_allocatedAssembly, 0, MEM_RELEASE);
}



JavaHook::JNIFrame::JNIFrame(JNIEnv* env, int ref_count) :
    m_env(env),
    m_isSuccess(false)
{
    m_isSuccess = env->PushLocalFrame(ref_count) == JNI_OK;
}

JavaHook::JNIFrame::~JNIFrame()
{
    if (!m_isSuccess)
        return;
    Pop();
}

void JavaHook::JNIFrame::Pop()
{
    if (!m_isSuccess)
        return;
    m_env->PopLocalFrame(nullptr);
    m_isSuccess = false; //prevent multiple pops
}

JavaHook::JNIFrame::operator bool()
{
    return m_isSuccess;
}
