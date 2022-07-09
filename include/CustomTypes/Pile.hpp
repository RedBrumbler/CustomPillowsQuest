#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include "CustomTypes/Pillow.hpp"
#include "CustomTypes/TexturePool.hpp"

DECLARE_CLASS_CODEGEN(CustomPillows, Pile, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_FIELD(TexturePool*, texturePool);
    DECLARE_INSTANCE_FIELD(ArrayW<Pillow*>, pillows);

    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, Start);
    DECLARE_INSTANCE_METHOD(void, Shuffle);
    
    public:
        void Hide(bool doHide = true);
)