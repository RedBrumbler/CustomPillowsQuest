#pragma once

#include "custom-types/shared/register.hpp"
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

DECLARE_CLASS_CODEGEN(MenuPillow, Updater, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_METHOD(void, Update);

    public:
        static void Construct();
        static void doDestroy();
)