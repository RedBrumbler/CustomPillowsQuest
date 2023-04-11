#include "UI/PillowUI.hpp"
#include "logging.hpp"

#include "bsml/shared/Helpers/getters.hpp"
#include "bsml/shared/BSML/MenuButtons/MenuButtons.hpp"
#include "bsml/shared/BSML.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"

DEFINE_TYPE(CustomPillows, PillowUI);

namespace CustomPillows {
    void PillowUI::ctor(GlobalNamespace::MainFlowCoordinator* mainFlowCoordinator, PillowSettingsFlowCoordinator* pillowSettingsFlowCoordinator) {
        DEBUG("ctor");
        _pillowSettingsFlowCoordinator = pillowSettingsFlowCoordinator;
        _mainFlowCoordinator = mainFlowCoordinator;
        _menuButton = BSML::MenuButton::Make_new("Custom Pillows", "Admire your waifus!", std::bind(&PillowUI::ShowFlow, this));
    }

    void PillowUI::ShowFlow() {
        _mainFlowCoordinator->YoungestChildFlowCoordinatorOrSelf()->PresentFlowCoordinator(_pillowSettingsFlowCoordinator, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, false, false);
    }

    void PillowUI::Initialize() {
        DEBUG("Init");
        BSML::Register::RegisterMenuButton(_menuButton);
    }

    void PillowUI::Dispose() {
        DEBUG("Dispose");
        BSML::Register::UnRegisterMenuButton(_menuButton);
    }
}