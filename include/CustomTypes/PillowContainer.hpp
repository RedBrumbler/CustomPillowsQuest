#pragma once

#include "custom-types-macros.hpp"

#include "Pile.hpp"

___DECLARE_CUSTOM_NAMESPACE_STRING_TYPE(CustomPillows, PillowContainer, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, UnityEngine::MonoBehaviour, "CustomPillows", "CustomPillows", {}, TYPE_ATTRIBUTE_PUBLIC | TYPE_ATTRIBUTE_BEFORE_FIELD_INIT, nullptr,
    DECLARE_INSTANCE_FIELD(ArrayW<Pile*>, piles);
    DECLARE_INSTANCE_METHOD(void, Awake);
)