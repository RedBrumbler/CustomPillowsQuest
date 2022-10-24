#include "CustomTypes/PillowManagers/MultiplayerMenuPillowManager.hpp"
#include "logging.hpp"
#include "config.hpp"

#include "custom-types/shared/delegate.hpp"

#include "GlobalNamespace/MultiplayerPlayersManager.hpp"
#include "System/Action_1.hpp"
DEFINE_TYPE(CustomPillows, MultiplayerMenuPillowManager);

namespace CustomPillows {
    void MultiplayerMenuPillowManager::ctor(::GlobalNamespace::LobbyGameStateModel* lobbyGameStateModel, GlobalPillowManager* globalPillowManager) {
        _lobbyGameStateModel = lobbyGameStateModel;
        _globalPillowManager = globalPillowManager;
    }

    void MultiplayerMenuPillowManager::MultiplayerGameStateDidChangeEvent(GlobalNamespace::MultiplayerGameState newGameState) {
        DEBUG("Switching to game state {}", newGameState);
        switch (newGameState) {
            default:
            case GlobalNamespace::MultiplayerGameState::None:
                // leave multi
                _globalPillowManager->Show(config.enabled);
                return;
            case GlobalNamespace::MultiplayerGameState::Lobby:
                // go into multi lobby
                _globalPillowManager->Show(config.enabled && config.keepInMulti);
                return;
            case GlobalNamespace::MultiplayerGameState::Game:
                // go into multi level
                _globalPillowManager->Show(config.enabled && config.keepInMulti && config.keepInLevel);
                return;
        }
    }

    void MultiplayerMenuPillowManager::Initialize() {
        auto delegate = custom_types::MakeDelegate<System::Action_1<GlobalNamespace::MultiplayerGameState>*>(
            std::function<void(GlobalNamespace::MultiplayerGameState)>(
                std::bind(&MultiplayerMenuPillowManager::MultiplayerGameStateDidChangeEvent, this, std::placeholders::_1)
            )
        );

        _lobbyGameStateModel->add_gameStateDidChangeAlwaysSentEvent(delegate);
    }

}