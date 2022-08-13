#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/AssetBundle.hpp"
#include "UnityEngine/GameObject.hpp"

#include "CustomTypes/Pile.hpp"
#include "CustomTypes/TexturePool.hpp"

DECLARE_CLASS_CODEGEN(CustomPillows, AssetManager, UnityEngine::MonoBehaviour, 
    DECLARE_INSTANCE_FIELD(UnityEngine::AssetBundle*, bundle);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, container);
    DECLARE_INSTANCE_FIELD(TexturePool*, texturePool);

    DECLARE_INSTANCE_FIELD(ArrayW<Pile*>, piles);

    DECLARE_INSTANCE_METHOD(void, OnDestroy);
    DECLARE_INSTANCE_METHOD(void, OnGameRestart);
    
    DECLARE_CTOR(ctor);

    public:
        static CustomPillows::AssetManager* get_instance();
        
        custom_types::Helpers::Coroutine LoadPillows(std::function<void(void)> onFinished = nullptr);
        
        Pile* GetPile(int index = -1);
        
    private:
        static SafePtrUnity<CustomPillows::AssetManager> instance;
        bool loaded;
        bool loading;
)