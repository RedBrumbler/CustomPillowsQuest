#include "UI/PillowSettingsGameplaySetupView.hpp"
#include "config.hpp"
#include "assets.hpp"

#include "UnityEngine/RectOffset.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

#include "HMUI/Touchable.hpp"

#include "Questui_ModSettingsInfos.hpp"

DEFINE_TYPE(CustomPillows, PillowSettingsGameplaySetupView);

#define SetPreferredSize(identifier, width, height)                                         \
    auto layout##identifier = identifier->get_gameObject()->GetComponent<LayoutElement*>(); \
    if (!layout##identifier)                                                                \
        layout##identifier = identifier->get_gameObject()->AddComponent<LayoutElement*>();  \
    layout##identifier->set_preferredWidth(width);                                          \
    layout##identifier->set_preferredHeight(height);                                        \
    auto fitter##identifier = identifier->GetComponent<ContentSizeFitter*>();               \
    fitter##identifier->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);         \
    fitter##identifier->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize)
    
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace HMUI;
using namespace QuestUI::BeatSaberUI;

namespace CustomPillows {
    void PillowSettingsGameplaySetupView::Inject(GlobalPillowManager* globalPillowManager) {
        this->globalPillowManager = globalPillowManager;
    }

    void PillowSettingsGameplaySetupView::DidActivate(bool firstActivation) {
        if (firstActivation) {
            get_gameObject()->AddComponent<Touchable*>();

            auto vertical = CreateVerticalLayoutGroup(get_transform());
            vertical->get_rectTransform()->set_anchoredPosition({35.0f, 22.5f});
            vertical->set_padding(RectOffset::New_ctor(2, 2, 2, 2));
            SetPreferredSize(vertical, 70.0f, 45.0f);

            auto bg = vertical->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
            bg->ApplyBackgroundWithAlpha("round-rect-panel", 0.8f);

            // toggle enabled
            enabledToggle = CreateToggle(vertical->get_transform(), "Enabled", config.enabled, std::bind(&PillowSettingsGameplaySetupView::OnEnabledToggled, this, std::placeholders::_1));
            keepInLevelToggle = CreateToggle(vertical->get_transform(), "Keep in Level", config.keepInLevel, std::bind(&PillowSettingsGameplaySetupView::OnKeepInLevelToggled, this, std::placeholders::_1));
            keepInMultiToggle = CreateToggle(vertical->get_transform(), "Keep in Multi", config.keepInMulti, std::bind(&PillowSettingsGameplaySetupView::OnKeepInMultiToggled, this, std::placeholders::_1));

            // toggle leave in level?
            // toggle leave in multi?

            auto constellationNamesVector = globalPillowManager->get_constellationNames();
            constellationNames = ArrayW<StringW>(static_cast<il2cpp_array_size_t>(constellationNamesVector.size()));
            int index = 0, active = 0;

            for (auto& constellationName : constellationNamesVector) {
                constellationNames[index] = constellationName;
                if (constellationName == config.lastActiveConstellation) {
                    active = index;
                }
                index++;
            }

            // choose constellation
            constellationChanger = CreateIncrementSetting(vertical->get_transform(), "Constellation", 0, 1.0f, active, std::bind(&PillowSettingsGameplaySetupView::OnConstellationChanged, this, std::placeholders::_1));
            constellationChanger->Text->SetText(constellationNames[active]);


            // shuffle images
            CreateUIButton(vertical->get_transform(), "Shuffle", std::bind(&PillowSettingsGameplaySetupView::OnShuffle, this));

            auto settingsVertical = CreateVerticalLayoutGroup(get_transform());
            settingsVertical->get_rectTransform()->set_anchoredPosition({72.5f, 47.5f});
            SetPreferredSize(settingsVertical, 5.0f, 5.0f);

            auto sprite = ArrayToSprite(IncludedAssets::arrow_png);

            CreateClickableImage(settingsVertical->get_transform(), sprite, std::bind(&PillowSettingsGameplaySetupView::OnOpenSettings, this));
        } else {
            UpdateOptions();
        }
    }

    void PillowSettingsGameplaySetupView::OnOpenSettings() {

        auto& modSettingsInfos = QuestUI::ModSettingsInfos::get();

        for (auto& info : modSettingsInfos) {
            if (info.modInfo.id == MOD_ID) {
                info.Present();
                break;
            }
        }
    }

    void PillowSettingsGameplaySetupView::OnShuffle() {
        if (config.enabled && globalPillowManager)
            globalPillowManager->Shuffle();
    }

    void PillowSettingsGameplaySetupView::OnEnabledToggled(bool value) {
        globalPillowManager->Hide(!value);

        config.enabled = value;
        SaveConfig();
    }

    void PillowSettingsGameplaySetupView::OnKeepInLevelToggled(bool value) {
        config.keepInLevel = value;
        SaveConfig();
    }

    void PillowSettingsGameplaySetupView::OnKeepInMultiToggled(bool value) {
        config.keepInMulti = value;
        SaveConfig();
    }

    void PillowSettingsGameplaySetupView::OnConstellationChanged(float value) {
        int index = (int)value;
        int max = constellationNames.size() - 1;
        // loop back
        if (index < 0) index = max;
        index %= (max + 1);
        StringW name = constellationNames[index];

        constellationChanger->Text->SetText(name);
        constellationChanger->CurrentValue = index;

        globalPillowManager->SetConstellation(index);
        
        config.lastActiveConstellation = static_cast<std::string>(name);
        SaveConfig();
    }

    void PillowSettingsGameplaySetupView::UpdateOptions() {
        enabledToggle->set_isOn(config.enabled);
        keepInLevelToggle->set_isOn(config.keepInLevel);
        keepInMultiToggle->set_isOn(config.keepInMulti);

        int index = 0, active = 0;

        for (auto& constellationName : constellationNames) {
            if (constellationName == config.lastActiveConstellation) {
                active = index;
            }
            index++;
        }
            
        StringW name = constellationNames[active];
        constellationChanger->Text->SetText(name);
        constellationChanger->CurrentValue = active;
    }
}