#pragma once
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "CustomTypes/Pillow.hpp"

struct PillowData;


DECLARE_CLASS_CODEGEN(MenuPillow, Pile, UnityEngine::MonoBehaviour,
    DECLARE_METHOD(Array<Pillow*>*, GetPillows);
    DECLARE_METHOD(void, Awake);
    DECLARE_METHOD(void, Update);
    DECLARE_METHOD(void, RandomizeTextures);
    
    private:
        int childCount = 0;
        int childIndex = 0;
        bool randomizeTextures = false;
    public:
        custom_types::Helpers::Coroutine RandomizeRoutine(PillowData* data);
        custom_types::Helpers::Coroutine SetupPillowsRoutine();

    REGISTER_FUNCTION(
        REGISTER_METHOD(GetPillows);
        REGISTER_METHOD(Awake);
        REGISTER_METHOD(Update);
        REGISTER_METHOD(RandomizeTextures);
    )
)