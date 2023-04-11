#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "UnityEngine/UI/Toggle.hpp"

#include "CustomTypes/PillowManagers/GlobalPillowManager.hpp"
#include "UI/PillowSettingsFlowCoordinator.hpp"

#define INTERFACES {classof(::Zenject::IInitializable*), classof(::System::IDisposable*)}

___DECLARE_TYPE_WRAPPER_INHERITANCE(CustomPillows, PillowSettingsGameplaySetupView, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, Il2CppObject, "CustomPillows", INTERFACES, 0, nullptr,
    DECLARE_INSTANCE_FIELD(UnityEngine::Transform*, root);
    DECLARE_INSTANCE_FIELD(GlobalPillowManager*, globalPillowManager);
    DECLARE_INSTANCE_FIELD(PillowSettingsFlowCoordinator*, pillowSettingsFlowCoordinator);
    DECLARE_INSTANCE_FIELD(GlobalNamespace::MainFlowCoordinator*, mainFlowCoordinator);
    DECLARE_INSTANCE_FIELD(ListWrapper<StringW>, constellationNames);
    
    DECLARE_INJECT_METHOD(void, Inject, GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator, PillowSettingsFlowCoordinator* pillowSettingsFlowCoordinator, GlobalPillowManager* globalPillowManager);
    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());

    DECLARE_BSML_PROPERTY(bool, Enabled);
    DECLARE_BSML_PROPERTY(bool, keepInLevel);
    DECLARE_BSML_PROPERTY(bool, keepInMulti);

    DECLARE_INSTANCE_METHOD(void, PostParse);
    DECLARE_INSTANCE_METHOD(void, OpenSettings);
    DECLARE_INSTANCE_METHOD(void, Shuffle);
    DECLARE_INSTANCE_METHOD(ListWrapper<StringW>, get_constellation_options);
    DECLARE_BSML_PROPERTY(StringW, constellation);
    DECLARE_CTOR(ctor);

)

#undef INTERFACES