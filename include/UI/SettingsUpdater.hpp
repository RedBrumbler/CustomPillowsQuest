#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

DECLARE_CLASS_CODEGEN(CustomPillows, SettingsUpdater, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_METHOD(void, OnEnable);
)