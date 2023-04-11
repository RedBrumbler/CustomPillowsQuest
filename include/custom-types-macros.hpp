#pragma once

#include "custom-types/shared/macros.hpp"
#define ___DECLARE_CUSTOM_NAMESPACE_STRING_TYPE(namespaze_, name_, typeEnum_, baseT, dllName_, namespaze_string_, interfaces_, flags_, baseCustom, ...) \
namespace namespaze_ { \
    class name_; \
} \
namespace namespaze_ { \
    class name_ : public baseT { \
        using ___TargetType = name_; \
        constexpr static auto ___Base__Size = sizeof(baseT); \
        friend ::custom_types::Register; \
        public: \
        struct ___TypeRegistration : ::custom_types::TypeRegistration { \
            ___TypeRegistration() { \
                ::custom_types::Register::AddType(this); \
                instance = this; \
            } \
            static inline std::vector<::custom_types::FieldRegistrator*> fields; \
            std::vector<::custom_types::FieldRegistrator*> const getFields() const override { \
                return fields; \
            } \
            static void addField(::custom_types::FieldRegistrator* inst) { \
                fields.push_back(inst); \
                ::custom_types::_logger().debug("Adding instance field: %s.%s new size: %lu", #name_, inst->name(), fields.size()); \
            } \
            static inline std::vector<::custom_types::StaticFieldRegistrator*> staticFields; \
            std::vector<::custom_types::StaticFieldRegistrator*> const getStaticFields() const override { \
                return staticFields; \
            } \
            static void addStaticFieldInstance(::custom_types::StaticFieldRegistrator* inst) { \
                staticFields.push_back(inst); \
                ::custom_types::_logger().debug("Adding static field: %s.%s new size: %lu", #name_, inst->name(), staticFields.size()); \
            } \
            static inline std::vector<::custom_types::MethodRegistrator*> methods; \
            std::vector<::custom_types::MethodRegistrator*> const getMethods() const override { \
                return methods; \
            } \
            static void addMethod(::custom_types::MethodRegistrator* inst) { \
                methods.push_back(inst); \
                ::custom_types::_logger().debug("Adding method: %s.%s new size: %lu", #name_, inst->name(), methods.size()); \
            } \
            static inline size_t staticFieldOffset; \
            static size_t addStaticField(size_t sz) { \
                auto tmp = staticFieldOffset; \
                staticFieldOffset += sz; \
                return tmp; \
            } \
            static char* st_fields; \
            char*& static_fields() override { \
                return st_fields; \
            } \
            size_t static_fields_size() const override { \
                return staticFieldOffset; \
            } \
            constexpr const char* name() const override { \
                return #name_; \
            } \
            constexpr const char* namespaze() const override { \
                return namespaze_string_; \
            } \
            constexpr const char* dllName() const override { \
                return dllName_; \
            } \
            Il2CppClass* baseType() const override { \
                return ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<baseT*>::get(); \
            } \
            std::vector<Il2CppClass*> const interfaces() const override { \
                return interfaces_; \
            } \
            constexpr Il2CppTypeEnum typeEnum() const override { \
                return typeEnum_; \
            } \
            constexpr uint32_t typeFlags() const override { \
                return flags_; \
            } \
            static Il2CppClass* klass_ptr; \
            Il2CppClass*& klass() const override { \
                return klass_ptr; \
            } \
            size_t size() const override { \
                return sizeof(___TargetType); \
            } \
            TypeRegistration* customBase() const override { \
                return baseCustom; \
            } \
            bool initialized() const override { \
                return init; \
            } \
            void setInitialized() const override { \
                init = true; \
            } \
            static bool init; \
            static TypeRegistration* instance; \
            static TypeRegistration* get() { \
                return instance; \
            } \
        }; \
        public: \
        __VA_ARGS__ \
    }; \
} \
template<> \
struct ::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<::namespaze_::name_*> { \
    static inline Il2CppClass* get() { \
        return ::namespaze_::name_::___TypeRegistration::klass_ptr; \
    } \
}; \
template<> \
struct ::il2cpp_utils::il2cpp_type_check::need_box<::namespaze_::name_> { \
    constexpr static bool value = false; \
};