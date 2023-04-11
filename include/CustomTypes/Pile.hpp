#pragma once

#include "custom-types-macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include "CustomTypes/Pillow.hpp"
#include "CustomTypes/TexturePool.hpp"

___DECLARE_CUSTOM_NAMESPACE_STRING_TYPE(CustomPillows, Pile, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, UnityEngine::MonoBehaviour, "CustomPillows", "CustomPillows", {}, TYPE_ATTRIBUTE_PUBLIC | TYPE_ATTRIBUTE_BEFORE_FIELD_INIT, nullptr,
    DECLARE_INSTANCE_FIELD(ArrayW<Pillow*>, pillows);
    DECLARE_INSTANCE_FIELD(int, pileType);
    DECLARE_INSTANCE_FIELD_PRIVATE(TexturePool*, _texturePool);

    DECLARE_INJECT_METHOD(void, Inject, TexturePool* texturePool);
    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, Shuffle);

    public:
        void Hide(bool doHide = true);
)