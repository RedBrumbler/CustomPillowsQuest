#include "UI/ConfigViewController.hpp"
#include "config.hpp"

#include "UnityEngine/RectOffset.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

#include "HMUI/Touchable.hpp"

DEFINE_TYPE(CustomPillows, ConfigViewController);

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
    void ConfigViewController::Inject(PillowManager* pillowManager) {
        this->pillowManager = pillowManager;
    }

    void ConfigViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (firstActivation) {
            get_gameObject()->AddComponent<Touchable*>();

            auto vertical = CreateVerticalLayoutGroup(get_transform());
            vertical->set_padding(RectOffset::New_ctor(2, 2, 2, 2));
            SetPreferredSize(vertical, 70.0f, 45.0f);

            auto bg = vertical->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
            bg->ApplyBackgroundWithAlpha("round-rect-panel", 0.8f);

            // toggle enabled
            enabledToggle = CreateToggle(vertical->get_transform(), "Enabled", config.enabled, std::bind(&ConfigViewController::OnEnabledToggled, this, std::placeholders::_1));
            keepInLevelToggle = CreateToggle(vertical->get_transform(), "Keep in Level", config.keepInLevel, std::bind(&ConfigViewController::OnKeepInLevelToggled, this, std::placeholders::_1));
            keepInMultiToggle = CreateToggle(vertical->get_transform(), "Keep in Multi", config.keepInMulti, std::bind(&ConfigViewController::OnKeepInMultiToggled, this, std::placeholders::_1));

            // toggle leave in level?
            // toggle leave in multi?

            auto constellationNamesVector = pillowManager->get_constellationNames();
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
            constellationChanger = CreateIncrementSetting(vertical->get_transform(), "Constellation", 0, 1.0f, active, std::bind(&ConfigViewController::OnConstellationChanged, this, std::placeholders::_1));
            constellationChanger->Text->SetText(constellationNames[active]);


            // shuffle images
            CreateUIButton(vertical->get_transform(), "Shuffle", std::bind(&ConfigViewController::OnShuffle, this));
        } else {
            UpdateOptions();
        }
    }

    void ConfigViewController::OnShuffle() {
        if (config.enabled && pillowManager)
            pillowManager->Shuffle();
    }

    void ConfigViewController::OnEnabledToggled(bool value) {
        pillowManager->Hide(!value);

        config.enabled = value;
        SaveConfig();
    }

    void ConfigViewController::OnKeepInLevelToggled(bool value) {
        config.keepInLevel = value;
        SaveConfig();
    }

    void ConfigViewController::OnKeepInMultiToggled(bool value) {
        config.keepInMulti = value;
        SaveConfig();
    }

    void ConfigViewController::OnConstellationChanged(float value) {
        int index = (int)value;
        int max = constellationNames.size() - 1;
        // loop back
        if (index < 0) index = max;
        index %= (max + 1);
        StringW name = constellationNames[index];

        constellationChanger->Text->SetText(name);
        constellationChanger->CurrentValue = index;

        pillowManager->SetConstellation(index);
        
        config.lastActiveConstellation = static_cast<std::string>(name);
        SaveConfig();
    }

    void ConfigViewController::UpdateOptions() {
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