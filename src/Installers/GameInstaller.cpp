#include "Installers/GameInstaller.hpp"

DEFINE_TYPE(CustomPillows, GameInstaller);

namespace CustomPillows {
    void GameInstaller::InstallBindings() {
        auto container = get_Container();
    }
}