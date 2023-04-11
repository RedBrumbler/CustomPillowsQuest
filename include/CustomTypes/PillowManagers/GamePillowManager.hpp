#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "GlobalPillowManager.hpp"
#include "Zenject/IInitializable.hpp"
#include "Zenject/DiContainer.hpp"
#include "System/IDisposable.hpp"

#define INTERFACES {classof(::Zenject::IInitializable*), classof(::System::IDisposable*)}

___DECLARE_TYPE_WRAPPER_INHERITANCE(CustomPillows, GamePillowManager, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, Il2CppObject, "CustomPillows", INTERFACES, 0, nullptr,
    DECLARE_PRIVATE_FIELD(GlobalPillowManager*, _globalPillowManager);
    DECLARE_PRIVATE_FIELD(bool, _multiplayer);

    DECLARE_CTOR(ctor, ::Zenject::DiContainer* container, GlobalPillowManager* globalPillowManager);

    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());
)

#undef INTERFACES