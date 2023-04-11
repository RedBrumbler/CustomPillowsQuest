#pragma once

#include "custom-types-macros.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Renderer.hpp"

___DECLARE_CUSTOM_NAMESPACE_STRING_TYPE(CustomPillows, Pillow, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, UnityEngine::MonoBehaviour, "CustomPillows", "CustomPillows", {}, TYPE_ATTRIBUTE_PUBLIC | TYPE_ATTRIBUTE_BEFORE_FIELD_INIT, nullptr,
    DECLARE_INSTANCE_FIELD(UnityEngine::Renderer*, pillowRenderer);
    DECLARE_INSTANCE_FIELD(UnityEngine::Material*, material);

    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, SetTexture, UnityEngine::Texture2D* texture);
)