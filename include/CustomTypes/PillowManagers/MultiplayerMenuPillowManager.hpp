#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "GlobalPillowManager.hpp"
#include "GlobalNamespace/LobbyGameStateModel.hpp"
#include "Zenject/IInitializable.hpp"
#include "Zenject/DiContainer.hpp"
#include "System/IDisposable.hpp"

#define INTERFACES {classof(::Zenject::IInitializable*) }

___DECLARE_TYPE_WRAPPER_INHERITANCE(CustomPillows, MultiplayerMenuPillowManager, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, Il2CppObject, "CustomPillows", INTERFACES, 0, nullptr,
    DECLARE_PRIVATE_FIELD(GlobalPillowManager*, _globalPillowManager);
    DECLARE_PRIVATE_FIELD(::GlobalNamespace::LobbyGameStateModel*, _lobbyGameStateModel);

    DECLARE_CTOR(ctor, ::GlobalNamespace::LobbyGameStateModel* lobbyGameStateModel, GlobalPillowManager* globalPillowManager);

    DECLARE_INSTANCE_METHOD(void, MultiplayerGameStateDidChangeEvent, GlobalNamespace::MultiplayerGameState newGameState);
    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
)

#undef INTERFACES