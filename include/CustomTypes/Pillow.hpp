#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/SkinnedMeshRenderer.hpp"

DECLARE_CLASS_CODEGEN(CustomPillows, Pillow, UnityEngine::MonoBehaviour, 
    DECLARE_INSTANCE_FIELD(UnityEngine::Material*, material);
    
    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, SetTexture, UnityEngine::Texture2D* texture);
)