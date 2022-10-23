#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/AssetBundle.hpp"
#include "UnityEngine/GameObject.hpp"
#include "System/IDisposable.hpp"

#include "CustomTypes/Pile.hpp"
#include "CustomTypes/TexturePool.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(CustomPillows, AssetManager, UnityEngine::MonoBehaviour, classof(::System::IDisposable*),
    DECLARE_INSTANCE_FIELD(UnityEngine::AssetBundle*, bundle);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, container);
    DECLARE_INSTANCE_FIELD(TexturePool*, texturePool);

    DECLARE_INSTANCE_FIELD(ArrayW<Pile*>, piles);
    DECLARE_INJECT_METHOD(void, Inject, TexturePool* texturePool);
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());
    DECLARE_INSTANCE_METHOD(void, OnDestroy);
    DECLARE_INSTANCE_METHOD(void, OnGameRestart);

    DECLARE_CTOR(ctor);

    public:
        custom_types::Helpers::Coroutine LoadPillows(std::function<void(void)> onFinished = nullptr);

        Pile* GetPile(int index = -1);

    private:
        bool loaded;
        bool loading;
)