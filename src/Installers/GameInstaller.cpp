#include "Installers/GameInstaller.hpp"

#include "CustomTypes/PillowManagers/GamePillowManager.hpp"

#include "Zenject/FromBinderNonGeneric.hpp"

DEFINE_TYPE(CustomPillows, GameInstaller);

namespace CustomPillows {
    void GameInstaller::InstallBindings() {
        auto container = get_Container();

        container->BindInterfacesAndSelfTo<GamePillowManager*>()->AsSingle();
    }
}