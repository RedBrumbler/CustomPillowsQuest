#pragma once

#include "custom-types/shared/macros.hpp"
#include "custom-types/shared/coroutine.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/Sprite.hpp"

#include "System/Collections/Generic/Dictionary_2.hpp"
#include "System/Collections/Generic/KeyValuePair_2.hpp"


DECLARE_CLASS_CODEGEN(CustomPillows, TexturePool, UnityEngine::MonoBehaviour,

    public:
        template<typename T, typename U>
        using Dictionary = System::Collections::Generic::Dictionary_2<T, U>;
        using NameToTexture = Dictionary<StringW, UnityEngine::Texture2D*>;
        using NameToTexturePair = System::Collections::Generic::KeyValuePair_2<StringW, UnityEngine::Texture2D*>;
    private:
        DECLARE_INSTANCE_FIELD(NameToTexture*, allTextures);
        DECLARE_INSTANCE_FIELD(NameToTexture*, activeTextures);
        DECLARE_INSTANCE_FIELD(NameToTexture*, inActiveTextures);

        DECLARE_INSTANCE_FIELD(ArrayW<NameToTexturePair>, activeTexturesArray);
        DECLARE_INSTANCE_FIELD(ArrayW<NameToTexturePair>, inActiveTexturesArray);


        DECLARE_INSTANCE_METHOD(void, OnDestroy);
        DECLARE_CTOR(ctor);
    public:

        UnityEngine::Texture2D* GetTexture(StringW path);
        UnityEngine::Sprite* GetSprite(StringW name);

        void ActivateTexture(StringW name);
        void DeactivateTexture(StringW name);
        
        custom_types::Helpers::Coroutine LoadTextures(std::function<void(void)> onFinished = nullptr);
    private:
        void UpdateArrays();
        bool loading;
        bool loaded;
)