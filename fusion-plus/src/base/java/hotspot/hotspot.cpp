#include "hotspot.h"
#include <util/logger.h>

// Source: https://github.com/Lefraudeur/RiptermsGhost/blob/master/HotSpot/HotSpot.cpp

extern "C" JNIIMPORT HotSpot::VMTypeEntry* gHotSpotVMTypes;
extern "C" JNIIMPORT HotSpot::VMStructEntry* gHotSpotVMStructs;

static HotSpot::VMTypeEntry* find_VMTypeEntry(const char* typeName)
{
    for (HotSpot::VMTypeEntry* entry = gHotSpotVMTypes; entry->typeName != nullptr; ++entry)
    {
        if (typeName && std::strcmp(typeName, entry->typeName)) continue;
		Logger::Log("Found VMTypeEntry. Type: %s", typeName);
        return entry;
    }
	Logger::Err("Failed to find VMTypeEntry. Type: %s", typeName);
    return nullptr;
}

static HotSpot::VMStructEntry* find_VMStructEntry(const char* typeName, const char* fieldName, bool isStatic)
{
    for (HotSpot::VMStructEntry* entry = gHotSpotVMStructs; entry->typeName != nullptr; ++entry)
    {
        if (typeName && std::strcmp(typeName, entry->typeName)) continue;
        if (fieldName && std::strcmp(fieldName, entry->fieldName)) continue;
        if (isStatic != (bool)entry->isStatic) continue;
        Logger::Log("Found VMStructEntry. Type: %s, Field: %s, Static: %s, Address: %p, Offset: %p", typeName, fieldName, isStatic ? "true" : "false", entry->address, entry->offset);
        return entry;
    }
	Logger::Err("Failed to find VMStructEntry. Type: %s, Field: %s, Static: %s", typeName, fieldName, isStatic ? "true" : "false");
    return nullptr;
}

void** HotSpot::ConstantPool::get_base()
{
    if (!this) return nullptr;

    int size = get_size();
    if (!size) return nullptr;

    return (void**)((uint8_t*)this + size);
}

int HotSpot::ConstantPool::get_size()
{
    static VMTypeEntry* ConstantPool_entry = find_VMTypeEntry("ConstantPool");
    if (!ConstantPool_entry) return 0;

    return (int)ConstantPool_entry->size;
}

int HotSpot::ConstantPool::get_length()
{
    if (!this) return 0;

    static VMStructEntry* _length_entry = find_VMStructEntry("Array<Klass*>", "_length", false);
    if (!_length_entry) return 0;

    return *(int*)((uint8_t*)this + _length_entry->offset);
}

HotSpot::ConstantPool* HotSpot::ConstMethod::get_constants()
{
    if (!this) return nullptr;

    static VMStructEntry* _constants_entry = find_VMStructEntry("InstanceKlass", "_constants", false);
    if (!_constants_entry) return nullptr;

    return *(ConstantPool**)((uint8_t*)this + _constants_entry->offset);
}

void HotSpot::ConstMethod::set_constants(ConstantPool* _constants)
{
    if (!this) return;

    static VMStructEntry* _constants_entry = find_VMStructEntry("ConstMethod", "_constants", false);
    if (!_constants_entry) return;

    *(ConstantPool**)((uint8_t*)this + _constants_entry->offset) = _constants;
}

unsigned short HotSpot::ConstMethod::get_name_index()
{
    if (!this) return 0;

    static VMStructEntry* _name_index_entry = find_VMStructEntry("ConstMethod", "_name_index", false);
    if (!_name_index_entry) return 0;

    return *(unsigned short*)((uint8_t*)this + _name_index_entry->offset);
}

unsigned short HotSpot::ConstMethod::get_signature_index()
{
    if (!this) return 0;

    static VMStructEntry* _signature_index_entry = find_VMStructEntry("ConstMethod", "_signature_index", false);
    if (!_signature_index_entry) return 0;

    return *(unsigned short*)((uint8_t*)this + _signature_index_entry->offset);
}

bool HotSpot::AccessFlags::is_static() const
{
    return (_flags & JVM_ACC_STATIC) != 0;
}

HotSpot::ConstMethod* HotSpot::Method::get_constMethod()
{
    if (!this) return nullptr;

    static VMStructEntry* _constMethod_entry = find_VMStructEntry("Method", "_constMethod", false);
    if (!_constMethod_entry) return nullptr;

    return *(ConstMethod**)((uint8_t*)this + _constMethod_entry->offset);
}

std::string HotSpot::Method::get_signature()
{
    if (!this) return "";

    ConstMethod* const_method = this->get_constMethod();
    int signature_index = const_method->get_signature_index();
    ConstantPool* cp = const_method->get_constants();
    Symbol** base = (Symbol**)cp->get_base();

    return base[signature_index]->to_string();
}

std::string HotSpot::Method::get_name()
{
    if (!this) return "";

    ConstMethod* const_method = this->get_constMethod();
    int name_index = const_method->get_name_index();
    ConstantPool* cp = const_method->get_constants();
    Symbol** base = (Symbol**)cp->get_base();

    return base[name_index]->to_string();
}

int HotSpot::Method::get_parameters_count()
{
    std::string signature = get_signature();
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

HotSpot::AccessFlags* HotSpot::Method::get_access_flags()
{
    if (!this) return nullptr;

    static VMStructEntry* _access_flags_entry = find_VMStructEntry("Method", "_access_flags", false);
    if (!_access_flags_entry) return nullptr;

    return (AccessFlags*)((uint8_t*)this + _access_flags_entry->offset);
}

void* HotSpot::Method::get_from_interpreted_entry()
{
    static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_from_interpreted_entry", false);
    if (!vm_entry) return nullptr;

    return *(void**)((uint8_t*)this + vm_entry->offset);
}

void HotSpot::Method::set_from_interpreted_entry(void* entry)
{
    static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_from_interpreted_entry", false);
    if (!vm_entry) return;

    *(void**)((uint8_t*)this + vm_entry->offset) = entry;
    return;
}

void* HotSpot::Method::get_from_compiled_entry()
{
    static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_from_compiled_entry", false);
    if (!vm_entry) return nullptr;

    return *(void**)((uint8_t*)this + vm_entry->offset);
}

void HotSpot::Method::set_from_compiled_entry(void* entry)
{
    static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_from_compiled_entry", false);
    if (!vm_entry) return;

    *(void**)((uint8_t*)this + vm_entry->offset) = entry;
    return;
}

void* HotSpot::Method::get_i2i_entry()
{
    static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_i2i_entry", false);
    if (!vm_entry) return nullptr;

    return *(void**)((uint8_t*)this + vm_entry->offset);
}

unsigned short* HotSpot::Method::get_flags()
{
    if (!this) return nullptr;
    static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_flags", false);
    if (!vm_entry)
        return nullptr;
    return (unsigned short*)((uint8_t*)this + vm_entry->offset);
}

void HotSpot::Method::set_dont_inline(bool enabled)
{
    unsigned short* _flags = get_flags();
    if (!_flags)
    {
        static VMStructEntry* vm_entry = find_VMStructEntry("Method", "_intrinsic_id", false);
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

void** HotSpot::frame::get_locals()
{
    if (!this) return nullptr;

    return *(void***)((uint8_t*)this + locals_offset); //48 on java8, 56 on java17
}

HotSpot::Method* HotSpot::frame::get_method()
{
    if (!this) return nullptr;

    return *(Method**)((uint8_t*)this - 24);
}

JNIEnv* HotSpot::Thread::get_env()
{
    if (!this) return nullptr;

    static VMStructEntry* _anchor_entry = find_VMStructEntry("JavaThread", "_anchor", false);
    if (!_anchor_entry) return nullptr;

    return (JNIEnv*)((uint8_t*)this + _anchor_entry->offset + 32);
}

uint32_t HotSpot::Thread::get_suspend_flags()
{
    static VMStructEntry* vm_entry = find_VMStructEntry("Thread", "_suspend_flags", false);
    if (!vm_entry) return 0;

    return *(uint32_t*)((uint8_t*)this + vm_entry->offset);
}

HotSpot::JavaThreadState HotSpot::Thread::get_thread_state()
{
    if (!this) return _thread_uninitialized;

    return *(JavaThreadState*)((uint8_t*)this + get_thread_state_offset());
}

void HotSpot::Thread::set_thread_state(JavaThreadState state)
{
    if (!this) return;

    *(JavaThreadState*)((uint8_t*)this + get_thread_state_offset()) = state;
}

int HotSpot::Thread::get_thread_state_offset()
{
    static VMStructEntry* vm_entry = find_VMStructEntry("JavaThread", "_thread_state", false);
    if (!vm_entry)
        return 0;
    return (int)vm_entry->offset;
}

std::string HotSpot::Symbol::to_string()
{
    if (!this) return "";

    static VMStructEntry* _body_entry = find_VMStructEntry("Symbol", "_body", false);
    if (!_body_entry) return "";

    static VMStructEntry* _length_entry = find_VMStructEntry("Symbol", "_length", false);
    if (!_length_entry) return "";

    unsigned char* _body = (uint8_t*)this + _body_entry->offset;
    unsigned short _length = *(unsigned short*)((uint8_t*)this + _length_entry->offset);
    std::string class_name((char*)_body, _length);
    return class_name;
}

bool HotSpot::init()
{
    if (!gHotSpotVMStructs || !gHotSpotVMTypes /*|| !gHotSpotVMIntConstants || !gHotSpotVMLongConstants*/)
    {
		Logger::Err("Failed to find gHotSpotVMStructs");
        return false;
    }
	Logger::Log("HotSpot initialized");
    return true;
}
