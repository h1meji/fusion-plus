#include "hotspot.h"

#include "util/logger/logger.h"

// Source: https://github.com/Lefraudeur/RiptermsGhost/blob/master/HotSpot/HotSpot.cpp

extern "C" JNIIMPORT HotSpot::VMTypeEntry* gHotSpotVMTypes;
extern "C" JNIIMPORT HotSpot::VMStructEntry* gHotSpotVMStructs;

static HotSpot::VMTypeEntry* FindVMTypeEntry(const char* typeName)
{
    for (HotSpot::VMTypeEntry* entry = gHotSpotVMTypes; entry->typeName != nullptr; ++entry)
    {
        if (typeName && std::strcmp(typeName, entry->typeName)) continue;
		LOG_INFO("Found VMTypeEntry. Type: %s", typeName);
        return entry;
    }
	LOG_ERROR("Failed to find VMTypeEntry. Type: %s", typeName);
    return nullptr;
}

static HotSpot::VMStructEntry* FindVMStructEntry(const char* typeName, const char* fieldName, bool isStatic)
{
    for (HotSpot::VMStructEntry* entry = gHotSpotVMStructs; entry->typeName != nullptr; ++entry)
    {
        if (typeName && std::strcmp(typeName, entry->typeName)) continue;
        if (fieldName && std::strcmp(fieldName, entry->fieldName)) continue;
        if (isStatic != (bool)entry->isStatic) continue;
        LOG_INFO("Found VMStructEntry. Type: %s, Field: %s, Static: %s, Address: %p, Offset: %p", typeName, fieldName, isStatic ? "true" : "false", entry->address, entry->offset);
        return entry;
    }
	LOG_ERROR("Failed to find VMStructEntry. Type: %s, Field: %s, Static: %s", typeName, fieldName, isStatic ? "true" : "false");
    return nullptr;
}

void** HotSpot::ConstantPool::GetBase()
{
    if (!this) return nullptr;

    int size = GetSize();
    if (!size) return nullptr;

    return (void**)((uint8_t*)this + size);
}

int HotSpot::ConstantPool::GetSize()
{
    static VMTypeEntry* ConstantPool_entry = FindVMTypeEntry("ConstantPool");
    if (!ConstantPool_entry) return 0;

    return (int)ConstantPool_entry->size;
}

int HotSpot::ConstantPool::GetLength()
{
    if (!this) return 0;

    static VMStructEntry* _length_entry = FindVMStructEntry("Array<Klass*>", "_length", false);
    if (!_length_entry) return 0;

    return *(int*)((uint8_t*)this + _length_entry->offset);
}

HotSpot::ConstantPool* HotSpot::ConstMethod::GetConstants()
{
    if (!this) return nullptr;

    static VMStructEntry* _constants_entry = FindVMStructEntry("InstanceKlass", "_constants", false);
    if (!_constants_entry) return nullptr;

    return *(ConstantPool**)((uint8_t*)this + _constants_entry->offset);
}

void HotSpot::ConstMethod::SetConstants(ConstantPool* _constants)
{
    if (!this) return;

    static VMStructEntry* _constants_entry = FindVMStructEntry("ConstMethod", "_constants", false);
    if (!_constants_entry) return;

    *(ConstantPool**)((uint8_t*)this + _constants_entry->offset) = _constants;
}

unsigned short HotSpot::ConstMethod::GetNameIndex()
{
    if (!this) return 0;

    static VMStructEntry* _name_index_entry = FindVMStructEntry("ConstMethod", "_name_index", false);
    if (!_name_index_entry) return 0;

    return *(unsigned short*)((uint8_t*)this + _name_index_entry->offset);
}

unsigned short HotSpot::ConstMethod::GetSignatureIndex()
{
    if (!this) return 0;

    static VMStructEntry* _signature_index_entry = FindVMStructEntry("ConstMethod", "_signature_index", false);
    if (!_signature_index_entry) return 0;

    return *(unsigned short*)((uint8_t*)this + _signature_index_entry->offset);
}

bool HotSpot::AccessFlags::IsStatic() const
{
    return (_flags & JVM_ACC_STATIC) != 0;
}

HotSpot::ConstMethod* HotSpot::Method::GetConstMethod()
{
    if (!this) return nullptr;

    static VMStructEntry* _constMethod_entry = FindVMStructEntry("Method", "_constMethod", false);
    if (!_constMethod_entry) return nullptr;

    return *(ConstMethod**)((uint8_t*)this + _constMethod_entry->offset);
}

std::string HotSpot::Method::GetSignature()
{
    if (!this) return "";

    ConstMethod* const_method = this->GetConstMethod();
    int signature_index = const_method->GetSignatureIndex();
    ConstantPool* cp = const_method->GetConstants();
    Symbol** base = (Symbol**)cp->GetBase();

    return base[signature_index]->ToString();
}

std::string HotSpot::Method::GetName()
{
    if (!this) return "";

    ConstMethod* const_method = this->GetConstMethod();
    int name_index = const_method->GetNameIndex();
    ConstantPool* cp = const_method->GetConstants();
    Symbol** base = (Symbol**)cp->GetBase();

    return base[name_index]->ToString();
}

int HotSpot::Method::GetParametersCount()
{
    std::string signature = GetSignature();
    if (signature.empty()) return 0;

    size_t parenthesis_index = signature.find(')');
    signature = signature.substr(1, parenthesis_index - 1);

    int param_count = 0;
    for (size_t i = 0; i < signature.size(); ++i)
    {
        char c = signature[i];
        if (c == 'L')
        {
            size_t cp_end = signature.find(';', i);
            i = cp_end;
        }
        ++param_count;
    }

    return param_count;
}

HotSpot::AccessFlags* HotSpot::Method::GetAccessFlags()
{
    if (!this) return nullptr;

    static VMStructEntry* _access_flags_entry = FindVMStructEntry("Method", "_access_flags", false);
    if (!_access_flags_entry) return nullptr;

    return (AccessFlags*)((uint8_t*)this + _access_flags_entry->offset);
}

void* HotSpot::Method::GetFromInterpretedEntry()
{
    static VMStructEntry* vm_entry = FindVMStructEntry("Method", "_from_interpreted_entry", false);
    if (!vm_entry) return nullptr;

    return *(void**)((uint8_t*)this + vm_entry->offset);
}

void HotSpot::Method::SetFromInterpretedEntry(void* entry)
{
    static VMStructEntry* vm_entry = FindVMStructEntry("Method", "_from_interpreted_entry", false);
    if (!vm_entry) return;

    *(void**)((uint8_t*)this + vm_entry->offset) = entry;
    return;
}

void* HotSpot::Method::GetFromCompiledEntry()
{
    static VMStructEntry* vm_entry = FindVMStructEntry("Method", "_from_compiled_entry", false);
    if (!vm_entry) return nullptr;

    return *(void**)((uint8_t*)this + vm_entry->offset);
}

void HotSpot::Method::SetFromCompiledEntry(void* entry)
{
    static VMStructEntry* vm_entry = FindVMStructEntry("Method", "_from_compiled_entry", false);
    if (!vm_entry) return;

    *(void**)((uint8_t*)this + vm_entry->offset) = entry;
    return;
}

void* HotSpot::Method::GetI2iEntry()
{
    static VMStructEntry* vm_entry = FindVMStructEntry("Method", "_i2i_entry", false);
    if (!vm_entry) return nullptr;

    return *(void**)((uint8_t*)this + vm_entry->offset);
}

unsigned short* HotSpot::Method::GetFlags()
{
    if (!this) return nullptr;
    static VMStructEntry* vm_entry = FindVMStructEntry("Method", "_flags", false);
    if (!vm_entry)
        return nullptr;
    return (unsigned short*)((uint8_t*)this + vm_entry->offset);
}

void HotSpot::Method::SetDontInline(bool enabled)
{
    unsigned short* _flags = GetFlags();
    if (!_flags)
    {
        static VMStructEntry* vm_entry = FindVMStructEntry("Method", "_intrinsic_id", false);
        if (!vm_entry) return;
        unsigned char* flags = ((uint8_t*)this + vm_entry->offset + 1);
        if (enabled)
            *flags |= (1 << 3);
        else
            *flags &= ~(1 << 3);
        return;
    }

    if (enabled)
        *_flags |= HotSpot::Flags::_dont_inline;
    else
        *_flags &= ~HotSpot::Flags::_dont_inline;
}

void** HotSpot::frame::GetLocals()
{
    if (!this) return nullptr;

    return *(void***)((uint8_t*)this + localsOffset); //48 on java8, 56 on java17
}

HotSpot::Method* HotSpot::frame::GetMethod()
{
    if (!this) return nullptr;

    return *(Method**)((uint8_t*)this - 24);
}

JNIEnv* HotSpot::Thread::GetEnv()
{
    if (!this) return nullptr;

    static VMStructEntry* _anchor_entry = FindVMStructEntry("JavaThread", "_anchor", false);
    if (!_anchor_entry) return nullptr;

    return (JNIEnv*)((uint8_t*)this + _anchor_entry->offset + 32);
}

uint32_t HotSpot::Thread::GetSuspendFlags()
{
    static VMStructEntry* vm_entry = FindVMStructEntry("Thread", "_suspend_flags", false);
    if (!vm_entry) return 0;

    return *(uint32_t*)((uint8_t*)this + vm_entry->offset);
}

HotSpot::JavaThreadState HotSpot::Thread::GetThreadState()
{
    if (!this) return _thread_uninitialized;

    return *(JavaThreadState*)((uint8_t*)this + GetThreadStateOffset());
}

void HotSpot::Thread::SetThreadState(JavaThreadState state)
{
    if (!this) return;

    *(JavaThreadState*)((uint8_t*)this + GetThreadStateOffset()) = state;
}

int HotSpot::Thread::GetThreadStateOffset()
{
    static VMStructEntry* vm_entry = FindVMStructEntry("JavaThread", "_thread_state", false);
    if (!vm_entry)
        return 0;
    return (int)vm_entry->offset;
}

std::string HotSpot::Symbol::ToString()
{
    if (!this) return "";

    static VMStructEntry* _body_entry = FindVMStructEntry("Symbol", "_body", false);
    if (!_body_entry) return "";

    static VMStructEntry* _length_entry = FindVMStructEntry("Symbol", "_length", false);
    if (!_length_entry) return "";

    unsigned char* _body = (uint8_t*)this + _body_entry->offset;
    unsigned short _length = *(unsigned short*)((uint8_t*)this + _length_entry->offset);
    std::string class_name((char*)_body, _length);
    return class_name;
}

bool HotSpot::Init()
{
    if (!gHotSpotVMStructs || !gHotSpotVMTypes /*|| !gHotSpotVMIntConstants || !gHotSpotVMLongConstants*/)
    {
		LOG_ERROR("Failed to find gHotSpotVMStructs");
        return false;
    }
	LOG_INFO("HotSpot initialized");
    return true;
}
