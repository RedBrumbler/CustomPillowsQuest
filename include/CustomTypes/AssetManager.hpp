#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/AssetBundle.hpp"
#include "UnityEngine/GameObject.hpp"
#include "System/IDisposable.hpp"
#include "Zenject/DiContainer.hpp"

#include "CustomTypes/PillowContainer.hpp"
#include "CustomTypes/TexturePool.hpp"


DECLARE_CLASS_CODEGEN_INTERFACES(CustomPillows, AssetManager, UnityEngine::MonoBehaviour, classof(::System::IDisposable*),
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::AssetBundle*, _bundle);
    DECLARE_INSTANCE_FIELD_PRIVATE(PillowContainer*, _pillowContainer);
    DECLARE_INSTANCE_FIELD_PRIVATE(TexturePool*, _texturePool);
    DECLARE_INSTANCE_FIELD_PRIVATE(Zenject::DiContainer*, _container);

    DECLARE_INJECT_METHOD(void, Inject, Zenject::DiContainer* container, TexturePool* texturePool);
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());

    DECLARE_CTOR(ctor);

    public:
        custom_types::Helpers::Coroutine LoadPillows(std::function<void(void)> onFinished = nullptr);

        Pile* GetPile(int index = -1);

    private:
        bool loaded;
        bool loading;
)