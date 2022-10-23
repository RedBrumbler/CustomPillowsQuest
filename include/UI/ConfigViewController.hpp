#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "HMUI/ViewController.hpp"
#include "UnityEngine/UI/Toggle.hpp"

#include "CustomTypes/PillowManager.hpp"
#include "questui/shared/CustomTypes/Components/Settings/IncrementSetting.hpp"

#ifndef DECLARE_OVERRIDE_METHOD_MATCH
#define DECLARE_OVERRIDE_METHOD_MATCH(retval, name, mptr, ...) \
    DECLARE_OVERRIDE_METHOD(retval, name, il2cpp_utils::il2cpp_type_check::MetadataGetter<mptr>::get(), __VA_ARGS__)
#endif

DECLARE_CLASS_CODEGEN(CustomPillows, ConfigViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(PillowManager*, pillowManager);
    DECLARE_INSTANCE_FIELD(ArrayW<StringW>, constellationNames);
    
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, enabledToggle);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, keepInMultiToggle);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, keepInLevelToggle);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, constellationChanger);

    DECLARE_INJECT_METHOD(void, Inject, PillowManager* pillowManager);
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    private:
        void OnShuffle();
        void OnEnabledToggled(bool value);
        void OnKeepInLevelToggled(bool value);
        void OnKeepInMultiToggled(bool value);
        void OnConstellationChanged(float value);
        void UpdateOptions();

)
