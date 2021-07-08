#pragma once
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Transform.hpp"
#include "constellation.hpp"
#include <vector>
#include <string>

DECLARE_CLASS_CODEGEN(MenuPillow, PillowManager, UnityEngine::MonoBehaviour,
    DECLARE_STATIC_METHOD(void, OnMenuSceneActivate);
    DECLARE_STATIC_METHOD(void, OnMenuSceneDeActivate);
    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, OnDestroy);
    DECLARE_INSTANCE_METHOD(void, RemoveLastPillow);


    public:
        static inline std::vector<MenuPillow::Constellation> constellations = {};
        static std::vector<MenuPillow::Constellation>* GetConstellations();
        UnityEngine::Transform* SpawnPile(pillowparams param);
        bool useSaved = false;
        bool shouldRandomizeOnReEnable = false;
        Constellation savedConstellation;
        
        void SetActiveConstellation(Constellation constellation);
        void SetActiveConstellation(std::string name);
        static void LoadConstellations();
        static void RandomizeTextures();
        
        static void OnModEnable();
        static void OnModDisable();
        
        static inline PillowManager* manager = nullptr;
)