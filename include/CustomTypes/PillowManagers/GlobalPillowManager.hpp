#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "Zenject/IInitializable.hpp"

#include "CustomTypes/AssetManager.hpp"
#include "CustomTypes/Pile.hpp"
#include "Constellation.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(CustomPillows, GlobalPillowManager, UnityEngine::MonoBehaviour, classof(::Zenject::IInitializable*),
    DECLARE_INJECT_METHOD(void, Inject, AssetManager* assetManager);
    DECLARE_INSTANCE_METHOD(void, OnGameRestart);
    DECLARE_INSTANCE_METHOD(void, PostPillowLoad);
    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
    
    DECLARE_INSTANCE_FIELD(bool, isHidden);
    DECLARE_INSTANCE_FIELD(AssetManager*, assetManager);
    DECLARE_INSTANCE_FIELD(ListWrapper<Pile*>, currentPiles);

    DECLARE_CTOR(ctor);

    public:
        void SetConstellation(int index);
        void SetConstellation(std::string_view name);
        void SetConstellation(const Constellation& constellation);
        /** @brief Hide all pillows dependent on parameter */
        void Hide(bool doHide = true);
        /** @brief Show all pillows dependent on parameter */
        void Show(bool doShow = true);
        void Shuffle();

        const Constellation& get_currentConstellation();
        std::vector<std::string> get_constellationNames();
    private:
        std::vector<Constellation> constellations;
        Constellation currentConstellation;
)