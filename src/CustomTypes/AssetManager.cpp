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
        void AssetManager::Inject(Zenject::DiContainer* container, TexturePool* texturePool) {
            _container = container;
            _texturePool = texturePool;
        }

        void AssetManager::ctor() {
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

            _bundle = bundleReq->get_assetBundle();
            Object::DontDestroyOnLoad(_bundle);

            auto assetReq = _bundle->LoadAssetAsync("_Pillows", reinterpret_cast<System::Type*>(csTypeOf(GameObject*)));
            assetReq->set_allowSceneActivation(true);
            DEBUG("Loading assets");
            // yield loading of asset
            co_yield reinterpret_cast<System::Collections::IEnumerator*>(assetReq);

            auto asset = reinterpret_cast<GameObject*>(assetReq->get_asset());
            auto go = Object::Instantiate(asset);
            Object::DontDestroyOnLoad(go);
            go->SetActive(false);
            _pillowContainer = go->GetComponent<PillowContainer*>();

            // wait for textures to load
            DEBUG("Loading textures");
            co_yield custom_types::Helpers::CoroutineHelper::New(_texturePool->LoadTextures());

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
            if (!loaded) {
                ERROR("Assets did not finish loading... returning null!");
                return nullptr;
            }

            if (!_pillowContainer || !_pillowContainer->m_CachedPtr.m_value) {
                INFO("Pillow container was not valid, returning null!");
                return nullptr;
            }

            auto& piles = _pillowContainer->piles;
            if (piles.size() == 0) {
                ERROR("Pillow container had 0 piles, returning null!");
                return nullptr;
            }

            if (index < 0) {
                DEBUG("Returning random pile");
                index = rand();
            }

            // ensure index falls in range
            index %= piles.size();

            DEBUG("Got Pile {}: {}", index, fmt::ptr(piles[index]));
            // instantiate and inject the pile
            auto clone = _container->InstantiatePrefab(piles[index])->GetComponent<Pile*>();
            return clone;
        }

        void AssetManager::Dispose() {
            INFO("Disposing of loaded assets for Custom Pillows!");
            if (_pillowContainer && _pillowContainer->m_CachedPtr.m_value) {
                UnityEngine::Object::DestroyImmediate(_pillowContainer->get_gameObject());
            }
            _pillowContainer = nullptr;

            if (_bundle && _bundle->m_CachedPtr.m_value) {
                _bundle->Unload(true);
            }
            _bundle = nullptr;
            loading = false;
            loaded = false;
        }
}