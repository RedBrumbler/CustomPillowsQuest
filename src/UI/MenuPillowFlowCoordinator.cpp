#include "UI/MenuPillowFlowCoordinator.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "questui/shared/BeatSaberUI.hpp"

DEFINE_CLASS(MenuPillow::MenuPillowFlowCoordinator);

namespace MenuPillow
{
    void MenuPillowFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (firstActivation)
        {
            SetTitle(il2cpp_utils::createcsstr("Custom Pillows Quest"), HMUI::ViewController::AnimationType::Out);
            showBackButton = true;

            configViewController = QuestUI::BeatSaberUI::CreateViewController<ConfigViewController*>();
            
            textureSelectorViewController  = QuestUI::BeatSaberUI::CreateViewController<TextureSelectorViewController*>();

            ProvideInitialViewControllers(textureSelectorViewController, nullptr, configViewController, nullptr, nullptr);
        }
    }

    void MenuPillowFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController)
    {
        this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
    }
}