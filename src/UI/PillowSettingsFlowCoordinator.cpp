#include "UI/PillowSettingsFlowCoordinator.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "questui/shared/BeatSaberUI.hpp"

DEFINE_TYPE(CustomPillows, PillowSettingsFlowCoordinator);

using namespace QuestUI::BeatSaberUI;

namespace CustomPillows {
    void PillowSettingsFlowCoordinator::Inject(ConfigViewController* configViewController, TextureSelectionViewController* textureSelectionViewController) {
        this->configViewController = configViewController;
        this->textureSelectionViewController = textureSelectionViewController;
    }

    void PillowSettingsFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (firstActivation) {
            ProvideInitialViewControllers(textureSelectionViewController, nullptr, configViewController, nullptr, nullptr);
            set_showBackButton(true);
            SetTitle("Custom Pillows", HMUI::ViewController::AnimationType::In);
        }
        
        configViewController->get_gameObject()->SetActive(true);
    }
    
    void PillowSettingsFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController) {
        configViewController->get_gameObject()->SetActive(false);
        parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
    }
}