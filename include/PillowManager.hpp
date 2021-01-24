#pragma once
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "constellation.hpp"
#include <vector>
#include <string>

DECLARE_CLASS_CODEGEN(MenuPillow, PillowManager, UnityEngine::MonoBehaviour,
    DECLARE_METHOD(void, OnMenuSceneActive);
    DECLARE_METHOD(void, OnMenuSceneInActive);
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, SpawnPillow);
    DECLARE_METHOD(void, RemoveLastPillow);

    public:
        std::vector<MenuPillow::Constellation> constellations;
    
    REGISTER_FUNCTION(PillowManager,
        REGISTER_METHOD(OnMenuSceneActive);
        REGISTER_METHOD(OnMenuSceneInActive);
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(SpawnPillow);
        REGISTER_METHOD(RemoveLastPillow);
    )
)