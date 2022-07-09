#include "UI/PillowSettingsFlowCoordinator.hpp"

#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

#include "questui/shared/BeatSaberUI.hpp"

DEFINE_TYPE(CustomPillows, PillowSettingsFlowCoordinator);

using namespace QuestUI::BeatSaberUI;

namespace CustomPillows {
    void PillowSettingsFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (firstActivation) {
            textureSelectionViewController = CreateViewController<CustomPillows::TextureSelectionViewController*>();
            configViewController = CreateViewController<CustomPillows::ConfigViewController*>();

            ProvideInitialViewControllers(textureSelectionViewController, nullptr, configViewController, nullptr, nullptr);
            set_showBackButton(true);
            SetTitle("Custom Pillows", HMUI::ViewController::AnimationType::In);
        }
    }
    
    void PillowSettingsFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController) {
        parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
    }

}