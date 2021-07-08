#include "CustomTypes/PileProvider.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"

#include <thread>

#include "UnityEngine/WaitUntil.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Coroutine.hpp"
#include "UnityEngine/AssetBundle.hpp"
#include "System/Collections/IEnumerator.hpp"
#include "System/Func_1.hpp"

#include "questui/shared/CustomTypes/Data/CustomDataType.hpp"

#include "static-defines.hpp"

#include "CustomTypes/Updater.hpp"

DEFINE_TYPE(MenuPillow, PileProvider);

extern Logger& getLogger();

namespace MenuPillow
{
    void PileProvider::LoadBundle(bool alsoLoadAssets)
    {
        if (bundleLoading) return;
        // make sure we can stop any other calls to this method from loading the bundle more than once
        bundleLoading = true;
        bundle = UnityEngine::AssetBundle::LoadFromFile(il2cpp_utils::newcsstr(PILLOWPATH));
        bundleLoading = false;
        
        /*
        bs_utils::AssetBundle::LoadFromFileAsync(PILLOWPATH, [&](bs_utils::AssetBundle* bundle){
            PileProvider::bundle = bundle;
            if (PileProvider::bundle) getLogger().info("Bundle Loaded!");
            else getLogger().error("Loaded bundle was nullptr");

            bundleLoading = false;
        });
        */

        if (alsoLoadAssets)
        {
            LoadAssets();
            // wait for bundle to finish loading
            /*
            Updater::Construct();
            std::thread assetLoader([&]{
                while (bundleLoading) usleep(1000);

                PileProvider::doLoadAssets = true;
            });
            */
           
            //assetLoader.detach();
        }
    }

    void PileProvider::ManualUpdate()
    {
        // if bundle finished, load assets from it
        if (doLoadAssets)
        {
            doLoadAssets = false;
            PileProvider::LoadAssets();
            Updater::doDestroy();
        }
    }

    void PileProvider::LoadAssets()
    {
        if (!bundle && !bundleLoading) 
        {
            getLogger().error("Tried loading assets from nullptr bundle");
            LoadBundle(true);
            return;
        }
        loadingAssets = true;

        UnityEngine::GameObject* obj = bundle->LoadAsset<UnityEngine::GameObject*>(il2cpp_utils::newcsstr("_Pillows"));
        UnityEngine::GameObject* providerObj = UnityEngine::GameObject::New_ctor();
        UnityEngine::Object::DontDestroyOnLoad(providerObj);
        providerObj->AddComponent<PileProvider*>()->OnAssetLoadComplete(obj);

        /*
        getLogger().info("Loading assets from bundle");
        bundle->LoadAssetAsync("_Pillows", [&](bs_utils::Asset* asset){
            UnityEngine::GameObject* obj = UnityEngine::GameObject::New_ctor();
            UnityEngine::Object::DontDestroyOnLoad(obj);
            obj->AddComponent<PileProvider*>()->OnAssetLoadComplete((UnityEngine::GameObject*)asset); 
        }, il2cpp_utils::GetSystemType("UnityEngine", "GameObject"));
        */
    }

    void PileProvider::OnAssetLoadComplete(UnityEngine::GameObject* container)
    {
        if (!container)
        {
            getLogger().error("Loaded asset was nullptr, aborting asset load");
            return;
        }
        // instantiate new of the loaded object so it's mine to keep
        PileProvider::container = UnityEngine::Object::Instantiate(container);
        UnityEngine::Object::DontDestroyOnLoad(PileProvider::container);
        
        // make it invisible
        PileProvider::container->SetActive(false);

        // for each child
        PileProvider::childCount = PileProvider::container->get_transform()->get_childCount();
        PileProvider::childIndex = 0;

        auto coroutine = UnityEngine::WaitUntil::New_ctor(il2cpp_utils::MakeDelegate<System::Func_1<bool>*>(classof(System::Func_1<bool>*), (Il2CppObject*)nullptr,
        +[](){
            if (PileProvider::childIndex >= PileProvider::childCount)
            {
                // we done with each child
                PileProvider::callback();
                return true;
            } 
            UnityEngine::Transform* child = PileProvider::container->get_transform()->GetChild(PileProvider::childIndex);
            Pile* pile = child->get_gameObject()->AddComponent<Pile*>();
            if (pile) PileProvider::piles.push_back(pile);
            PileProvider::childIndex++;
            return false;
        }));

        UnityEngine::MonoBehaviour::StartCoroutine(reinterpret_cast<System::Collections::IEnumerator*>(coroutine));
        // unload bundle
        ((UnityEngine::AssetBundle*)this->bundle)->Unload(false);
    }

    Pile* PileProvider::GetPile(int index)
    {
        // if none loaded return nullptr
        if (!piles.size()) return nullptr;
        // if no index given we want a random pile
        if (index < 0) index = rand();
        //make sure index falls within bounds
        index %= piles.size();
        // instantiate the pile
        UnityEngine::GameObject* newPile = UnityEngine::Object::Instantiate(piles[index]->get_gameObject());
        // return it's pile component
        return newPile->GetComponent<Pile*>();
    }
}