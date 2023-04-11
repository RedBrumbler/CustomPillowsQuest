#include "Installers/MultiplayerMenuInstaller.hpp"
#include "logging.hpp"

#include "CustomTypes/PillowManagers/MultiplayerMenuPillowManager.hpp"

#include "Zenject/FromBinderNonGeneric.hpp"

DEFINE_TYPE(CustomPillows, MultiplayerMenuInstaller);

namespace CustomPillows {
    void MultiplayerMenuInstaller::InstallBindings() {
        DEBUG("Installing Bindings!");
        auto container = get_Container();
        container->BindInterfacesAndSelfTo<MultiplayerMenuPillowManager*>()->AsSingle();
    }
}