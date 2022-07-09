#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include "CustomTypes/AssetManager.hpp"
#include "CustomTypes/Pile.hpp"
#include "Constellation.hpp"

DECLARE_CLASS_CODEGEN(CustomPillows, PillowManager, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_METHOD(void, OnGameRestart);
    DECLARE_INSTANCE_METHOD(void, PostPillowLoad);
    
    DECLARE_INSTANCE_FIELD(AssetManager*, assetManager);
    DECLARE_INSTANCE_FIELD(ListWrapper<Pile*>, currentPiles);

    DECLARE_CTOR(ctor);

    public:
        static PillowManager* get_instance();
        void SetConstellation(int index);
        void SetConstellation(std::string_view name);
        void SetConstellation(const Constellation& constellation);
        
        void Hide(bool doHide = true);
        void Shuffle();

        std::vector<std::string> get_constellationNames();
    private:
        static PillowManager* instance;
        std::vector<Constellation> constellations;
        Constellation currentConstellation;
)