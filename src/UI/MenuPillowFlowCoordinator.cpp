#include "UI/MenuPillowFlowCoordinator.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "questui/shared/BeatSaberUI.hpp"

DEFINE_TYPE(MenuPillow, MenuPillowFlowCoordinator);

namespace MenuPillow
{
    void MenuPillowFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (firstActivation)
        {
            // set the title ofc
            SetTitle("Custom Pillows", HMUI::ViewController::AnimationType::Out);
            showBackButton = true; // we wanna go back

            // make the config view controller
            configViewController = QuestUI::BeatSaberUI::CreateViewController<ConfigViewController*>();
            
            // make the texture selector
            textureSelectorViewController  = QuestUI::BeatSaberUI::CreateViewController<TextureSelectorViewController*>();

            // give the game the view controllers to present whenever this menu gets activated
            ProvideInitialViewControllers(textureSelectorViewController, nullptr, configViewController, nullptr, nullptr);
        }
    }

    void MenuPillowFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController)
    {
        // dismiss this flow coordinator
        this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
    }
}