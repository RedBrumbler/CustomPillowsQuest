#pragma once
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "Pillow.hpp"

DECLARE_CLASS_CODEGEN(MenuPillow, Pile, UnityEngine::MonoBehaviour,
    DECLARE_METHOD(Array<Pillow*>*, GetPillows);
    DECLARE_METHOD(void, Awake);
    private:
        int childCount = 0;
        int childIndex = 0;
    REGISTER_FUNCTION(Pile,
        REGISTER_METHOD(GetPillows);
        REGISTER_METHOD(Awake);
    )
)