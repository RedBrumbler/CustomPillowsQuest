#include "UI/SettingsUpdater.hpp"

#include "bsml/shared/BSML/Components/Settings/BaseSetting.hpp"

DEFINE_TYPE(CustomPillows, SettingsUpdater);

namespace CustomPillows {
    void SettingsUpdater::OnEnable() {
        auto settings = GetComponentsInChildren<BSML::BaseSetting*>(true);

        for (auto setting : settings) {
            il2cpp_utils::RunMethod(setting, "ReceiveValue");
        }
    }
}