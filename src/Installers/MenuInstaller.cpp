#include "Installers/MenuInstaller.hpp"
#include "logging.hpp"

#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"
#include "Zenject/ConcreteIdBinderGeneric_1.hpp"

#include "UI/PillowSettingsFlowCoordinator.hpp"
#include "UI/TextureSelectionViewController.hpp"
#include "UI/ConfigViewController.hpp"
#include "UI/PillowUI.hpp"
#include "UI/PillowSettingsGameplaySetupView.hpp"

#include "lapiz/shared/utilities/ZenjectExtensions.hpp"
DEFINE_TYPE(CustomPillows, MenuInstaller);

using namespace ::Lapiz::Zenject::ZenjectExtensions;

namespace CustomPillows {
    void MenuInstaller::InstallBindings() {
        INFO("Installing bindings!");
        auto container = get_Container();

        FromNewComponentOnNewGameObject(container->Bind<CustomPillows::PillowSettingsFlowCoordinator*>())->AsSingle();
        FromNewComponentAsViewController(container->BindInterfacesAndSelfTo<CustomPillows::TextureSelectionViewController*>())->AsSingle();
        FromNewComponentAsViewController(container->BindInterfacesAndSelfTo<CustomPillows::ConfigViewController*>())->AsSingle();
        container->BindInterfacesAndSelfTo<PillowSettingsGameplaySetupView*>()->AsSingle();
        container->BindInterfacesAndSelfTo<PillowUI*>()->AsSingle();
    }
}