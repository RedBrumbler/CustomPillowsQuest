#pragma once
#include "UnityEngine/AssetBundle.hpp"
#include "CustomTypes/Pile.hpp"
#include "UnityEngine/GameObject.hpp"
#include <functional>

#include "custom-types/shared/register.hpp"
#include "custom-types/shared/macros.hpp"

DECLARE_CLASS_CODEGEN(MenuPillow, PileProvider, UnityEngine::MonoBehaviour,
    DECLARE_STATIC_METHOD(void, LoadBundle, bool alsoLoadAssets = false);
    DECLARE_STATIC_METHOD(void, LoadAssets);
    DECLARE_STATIC_METHOD(Pile*, GetPile, int index = -1);
    DECLARE_INSTANCE_METHOD(void, OnAssetLoadComplete, UnityEngine::GameObject* pillowContainer);
    DECLARE_STATIC_METHOD(void, ManualUpdate);
    
    public:
        static inline std::function<void()> callback = []{};
        static int get_pilesize() 
        {
            return piles.size();
        }
    private:
        static inline UnityEngine::GameObject* container = nullptr;

        static inline UnityEngine::AssetBundle* bundle = nullptr;
        static inline std::vector<Pile*> piles = {};

        static inline bool bundleLoading = false;
        static inline bool loadingAssets = false;
        static inline bool doLoadAssets = false;

        static inline int childIndex = 0;
        static inline int childCount = 0;
)