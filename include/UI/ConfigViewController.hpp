#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "bsml/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/UI/Toggle.hpp"

#include "CustomTypes/PillowManagers/GlobalPillowManager.hpp"

DECLARE_CLASS_CODEGEN(CustomPillows, ConfigViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(GlobalPillowManager*, globalPillowManager);
    DECLARE_INSTANCE_FIELD(ListWrapper<StringW>, constellationNames);
    
    DECLARE_INJECT_METHOD(void, Inject, GlobalPillowManager* globalPillowManager);
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    DECLARE_BSML_PROPERTY(bool, Enabled);
    DECLARE_BSML_PROPERTY(bool, keepInLevel);
    DECLARE_BSML_PROPERTY(bool, keepInMulti);

    DECLARE_INSTANCE_METHOD(void, Shuffle);
    DECLARE_INSTANCE_METHOD(ListWrapper<StringW>, get_constellation_options);
    DECLARE_BSML_PROPERTY(StringW, constellation);
    DECLARE_CTOR(ctor);
    private:
        void UpdateOptions();

)
