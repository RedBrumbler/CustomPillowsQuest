#pragma once
#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/register.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Texture2D.hpp"

DECLARE_CLASS_CODEGEN(MenuPillow, Pillow, UnityEngine::MonoBehaviour, 
    DECLARE_METHOD(void, Init, UnityEngine::Texture2D* texture);
    public:
        void InitFromName(std::string texName);

    REGISTER_FUNCTION(Pillow,
        REGISTER_METHOD(Init);
    )
)