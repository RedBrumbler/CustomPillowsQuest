#include "CustomTypes/AssetManager.hpp"
#include "assets.hpp"
#include "logging.hpp"

#include "UnityEngine/Object.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/AssetBundleCreateRequest.hpp"
#include "UnityEngine/AssetBundleRequest.hpp"

#include "System/Collections/IEnumerator.hpp"

#include <stdlib.h>

DEFINE_TYPE(CustomPillows, AssetManager);

using namespace UnityEngine;

namespace CustomPillows {
        AssetManager* AssetManager::instance = nullptr;
        
        void AssetManager::ctor() {
            loading = false;
            loaded = false;

            texturePool = get_gameObject()->AddComponent<TexturePool*>();
        }

        AssetManager* AssetManager::get_instance() {
            if (instance) return instance;
            static ConstString assetManagerName{"AssetManager"};
            auto go = GameObject::New_ctor(assetManagerName);
            Object::DontDestroyOnLoad(go);
            instance = go->AddComponent<AssetManager*>();
            return instance;
        }

        void AssetManager::OnDestroy() {
            instance = nullptr;
            loading = false;
            loaded = false;
        }

        custom_types::Helpers::Coroutine AssetManager::LoadPillows(std::function<void(void)> onFinished) {
            if (loading || loaded) co_return;
            INFO("Loading Pillows...");
            loading = true;
            // resolve load bundle from memory
            using AssetBundle_LoadFromMemoryAsync = function_ptr_t<UnityEngine::AssetBundleCreateRequest*, ArrayW<uint8_t>, int>;
            static AssetBundle_LoadFromMemoryAsync assetBundle_LoadFromMemoryAsync = reinterpret_cast<AssetBundle_LoadFromMemoryAsync>(il2cpp_functions::resolve_icall("UnityEngine.AssetBundle::LoadFromMemoryAsync_Internal"));
            
            auto bundleReq = assetBundle_LoadFromMemoryAsync(IncludedAssets::container_pillows, 0);
            bundleReq->set_allowSceneActivation(true);

            DEBUG("Loading bundle");
            // yield loading of bundle
            co_yield reinterpret_cast<System::Collections::IEnumerator*>(bundleReq);

            bundle = bundleReq->get_assetBundle();
            Object::DontDestroyOnLoad(bundle);

            auto assetReq = bundle->LoadAssetAsync("_Pillows", reinterpret_cast<System::Type*>(csTypeOf(GameObject*)));
            assetReq->set_allowSceneActivation(true);
            DEBUG("Loading assets");
            // yield loading of asset
            co_yield reinterpret_cast<System::Collections::IEnumerator*>(assetReq);

            auto asset = reinterpret_cast<GameObject*>(assetReq->get_asset());
            container = Object::Instantiate(asset);
            Object::DontDestroyOnLoad(container);
            container->SetActive(false);

            // parse loaded assets into array
            auto transform = container->get_transform();
            int childCount = transform->get_childCount();

            piles = ArrayW<Pile*>(static_cast<il2cpp_array_size_t>(childCount));

            DEBUG("Creating Piles");
            for (int i = 0; i < childCount; i++) {
                piles[i] = transform->GetChild(i)->get_gameObject()->AddComponent<Pile*>();
            }

            for (auto pile : piles) {
                auto transform = pile->get_transform();
                int childCount = transform->get_childCount();
                for (int i = 0; i < childCount; i++) {
                    auto child = transform->GetChild(i);
                    auto pillow = child->get_gameObject()->AddComponent<Pillow*>();
                }
            }

            // wait for textures to load
            DEBUG("Loading textures");
            co_yield custom_types::Helpers::CoroutineHelper::New(texturePool->LoadTextures());

            loaded = true;
            
            DEBUG("OnFinished");
            // run onFinished if given
            if (onFinished)
                onFinished();

            loading = false;
            INFO("Pillows Loaded!");
            // profit
            co_return;
        }

        Pile* AssetManager::GetPile(int index) {
            if (!loaded || piles.Length() == 0) return nullptr;
            if (index < 0) {
                index = rand();
            }

            index %= piles.Length();

            DEBUG("Got Pile {}: {}", index, fmt::ptr(piles[index]));
            auto clone = Object::Instantiate(piles[index]);
            clone->texturePool = texturePool;
            return clone;
        }


        void AssetManager::OnGameRestart() {
            if (container)
            {
                Object::DestroyImmediate(container);
                container = nullptr;
            }

            if (bundle)
            {
                bundle->Unload(true);
                bundle = nullptr;
            }

            instance = nullptr;
            Object::DestroyImmediate(this->get_gameObject());
        }
}