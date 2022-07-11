#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/UI/Toggle.hpp"

#include "CustomTypes/PillowManager.hpp"
#include "questui/shared/CustomTypes/Components/Settings/IncrementSetting.hpp"

DECLARE_CLASS_CODEGEN(CustomPillows, PillowSettingsGameplaySetupView, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(PillowManager*, pillowManager);
    DECLARE_INSTANCE_FIELD(ArrayW<StringW>, constellationNames);

    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, enabledToggle);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, keepInMultiToggle);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Toggle*, keepInLevelToggle);
    DECLARE_INSTANCE_FIELD(QuestUI::IncrementSetting*, constellationChanger);

    DECLARE_INSTANCE_METHOD(void, DidActivate, bool firstActivation);

    private:
        void OnOpenSettings();
        void OnShuffle();
        void OnEnabledToggled(bool value);
        void OnKeepInLevelToggled(bool value);
        void OnKeepInMultiToggled(bool value);
        void OnConstellationChanged(float value);
        void UpdateOptions();

)