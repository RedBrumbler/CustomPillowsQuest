#include "UI/ConfigViewController.hpp"
#include "config.hpp"
#include "logging.hpp"
#include "assets.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSML/Components/Settings/BaseSetting.hpp"

DEFINE_TYPE(CustomPillows, ConfigViewController);

namespace CustomPillows {
    void ConfigViewController::ctor() {
        constellationNames = List<StringW>::New_ctor();
    }

    void ConfigViewController::Inject(GlobalPillowManager* globalPillowManager) {
        this->globalPillowManager = globalPillowManager;
        auto constellationNamesVector = globalPillowManager->get_constellationNames();
        constellationNames->EnsureCapacity(constellationNamesVector.size());

        for (auto& name : constellationNamesVector) {
            constellationNames->Add(name);
        }
    }

    void ConfigViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (firstActivation) {
            BSML::parse_and_construct(IncludedAssets::ConfigView_bsml, get_transform(), this);
        } else {
            UpdateOptions();
        }
    }

    bool ConfigViewController::get_Enabled() { return config.enabled; }
    void ConfigViewController::set_Enabled(bool value) { 
        globalPillowManager->Hide(!value);

        config.enabled = value;        
        SaveConfig();
    }

    bool ConfigViewController::get_keepInLevel() { return config.keepInLevel; }
    void ConfigViewController::set_keepInLevel(bool value) { 
        config.keepInLevel = value;
        SaveConfig();
    }

    bool ConfigViewController::get_keepInMulti() { return config.keepInMulti; }
    void ConfigViewController::set_keepInMulti(bool value) { 
        config.keepInMulti = value;
        SaveConfig();
    }

    ListWrapper<StringW> ConfigViewController::get_constellation_options() {
        return constellationNames;
    }

    StringW ConfigViewController::get_constellation() {
        auto value = globalPillowManager->get_currentConstellation().get_name();
        return StringW(value);
    }

    void ConfigViewController::set_constellation(StringW value) {
        config.lastActiveConstellation = static_cast<std::string>(value);
        globalPillowManager->SetConstellation(config.lastActiveConstellation);
        
        SaveConfig();
    }

    void ConfigViewController::Shuffle() {
        DEBUG("Shuffle");
        if (config.enabled && globalPillowManager)
            globalPillowManager->Shuffle();
    }

    void ConfigViewController::UpdateOptions() {
        auto settings = GetComponentsInChildren<BSML::BaseSetting*>(true);

        for (auto setting : settings) {
            il2cpp_utils::RunMethod(setting, "ReceiveValue");
        }
    }
}