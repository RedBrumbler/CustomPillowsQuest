#include "UI/PillowSettingsGameplaySetupView.hpp"
#include "UI/SettingsUpdater.hpp"
#include "config.hpp"
#include "logging.hpp"
#include "assets.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "bsml/shared/BSML.hpp"

DEFINE_TYPE(CustomPillows, PillowSettingsGameplaySetupView);

namespace CustomPillows {
    void PillowSettingsGameplaySetupView::ctor() {
        constellationNames = List<StringW>::New_ctor();
    }

    void PillowSettingsGameplaySetupView::Initialize() {
        BSML::Register::RegisterGameplaySetupTab("Custom Pillows", MOD_ID "_gameplaySetupTab", this);
    }

    void PillowSettingsGameplaySetupView::Dispose() {
        BSML::Register::UnRegisterGameplaySetupTab("Custom Pillows");
    }

    void PillowSettingsGameplaySetupView::PostParse() {
        root->get_gameObject()->AddComponent<SettingsUpdater*>();
    }

    void PillowSettingsGameplaySetupView::Inject(GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator, PillowSettingsFlowCoordinator* pillowSettingsFlowCoordinator, GlobalPillowManager* globalPillowManager) {
        this->mainFlowCoordinator = mainFlowCoordinator;
        this->pillowSettingsFlowCoordinator = pillowSettingsFlowCoordinator;
        this->globalPillowManager = globalPillowManager;
        auto constellationNamesVector = globalPillowManager->get_constellationNames();
        constellationNames->EnsureCapacity(constellationNamesVector.size());

        for (auto& name : constellationNamesVector) {
            constellationNames->Add(name);
        }
    }

    void PillowSettingsGameplaySetupView::OpenSettings() {
        auto fc = mainFlowCoordinator->YoungestChildFlowCoordinatorOrSelf();

        fc->PresentFlowCoordinator(pillowSettingsFlowCoordinator, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, false, false);
    }

    bool PillowSettingsGameplaySetupView::get_Enabled() { return config.enabled; }
    void PillowSettingsGameplaySetupView::set_Enabled(bool value) { 
        globalPillowManager->Hide(!value);

        config.enabled = value;        
        SaveConfig();
    }

    bool PillowSettingsGameplaySetupView::get_keepInLevel() { return config.keepInLevel; }
    void PillowSettingsGameplaySetupView::set_keepInLevel(bool value) { 
        config.keepInLevel = value;
        SaveConfig();
    }

    bool PillowSettingsGameplaySetupView::get_keepInMulti() { return config.keepInMulti; }
    void PillowSettingsGameplaySetupView::set_keepInMulti(bool value) { 
        config.keepInMulti = value;
        SaveConfig();
    }

    ListWrapper<StringW> PillowSettingsGameplaySetupView::get_constellation_options() {
        return constellationNames;
    }

    StringW PillowSettingsGameplaySetupView::get_constellation() {
        auto value = globalPillowManager->get_currentConstellation().get_name();
        return StringW(value);
    }

    void PillowSettingsGameplaySetupView::set_constellation(StringW value) {
        config.lastActiveConstellation = static_cast<std::string>(value);
        globalPillowManager->SetConstellation(config.lastActiveConstellation);
        
        SaveConfig();
    }

    void PillowSettingsGameplaySetupView::Shuffle() {
        if (config.enabled && globalPillowManager)
            globalPillowManager->Shuffle();
    }
}