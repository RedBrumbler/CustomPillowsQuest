#include "CustomTypes/PillowManagers/GamePillowManager.hpp"
#include "config.hpp"

#include "GlobalNamespace/MultiplayerPlayersManager.hpp"
DEFINE_TYPE(CustomPillows, GamePillowManager);

namespace CustomPillows {
    void GamePillowManager::ctor(::Zenject::DiContainer* container, GlobalPillowManager* globalPillowManager) {
        _globalPillowManager = globalPillowManager;

        _multiplayer = container->TryResolve<GlobalNamespace::MultiplayerPlayersManager*>();
    }

    void GamePillowManager::Initialize() {
        // from menu -> game
        if (_multiplayer) {
            _globalPillowManager->Show(config.enabled && config.keepInLevel && config.keepInMulti);
        } else {
            _globalPillowManager->Show(config.enabled && config.keepInLevel);
        }
    }

    void GamePillowManager::Dispose() {
        // from game -> menu
        if (_multiplayer) {
            _globalPillowManager->Show(config.enabled && config.keepInMulti);
        } else {
            _globalPillowManager->Show(config.enabled);
        }
    }
}