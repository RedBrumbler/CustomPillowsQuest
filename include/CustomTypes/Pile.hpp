#pragma once
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "CustomTypes/Pillow.hpp"

struct PillowData;


DECLARE_CLASS_CODEGEN(MenuPillow, Pile, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_METHOD(ArrayW<Pillow*>, GetPillows);
    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_INSTANCE_METHOD(void, RandomizeTextures);
    
    private:
        int childCount = 0;
        int childIndex = 0;
        bool randomizeTextures = false;
    public:
        custom_types::Helpers::Coroutine RandomizeRoutine(PillowData* data);
        custom_types::Helpers::Coroutine SetupPillowsRoutine();
)