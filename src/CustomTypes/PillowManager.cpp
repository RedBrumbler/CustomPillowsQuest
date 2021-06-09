#include "config.hpp"
#include "CustomTypes/PillowManager.hpp"
#include "UnityEngine/Object.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Resources.hpp"
#include "CustomTypes/PileProvider.hpp"
#include "TexturePool.hpp"
#include "static-defines.hpp"

DEFINE_TYPE(MenuPillow::PillowManager);

using namespace UnityEngine;

extern config_t config;
extern Logger& getLogger();

namespace MenuPillow
{
    void PillowManager::OnMenuSceneActivate()
    {
        if (!manager)
        {
            Array<PillowManager*>* managers = Resources::FindObjectsOfTypeAll<PillowManager*>();
            manager = managers->values[0];
        }
        if (!manager) 
        {
            getLogger().error("Manager was nullptr");
            return;
        }
        manager->get_gameObject()->SetActive(true);
    }

    void PillowManager::OnMenuSceneDeActivate()
    {
        if (!manager)
        {
            Array<PillowManager*>* managers = Resources::FindObjectsOfTypeAll<PillowManager*>();
            manager = managers->values[0];
        }
        if (!manager) 
        {
            getLogger().error("Manager was nullptr");
            return;
        }
        manager->get_gameObject()->SetActive(false);
    }

    void PillowManager::Awake()
    {
        TexturePool::LoadAllTextures();
        //LoadConstellations();
                
        if (!(PileProvider::get_pilesize() > 0)) 
        {
            PileProvider::LoadBundle(true);
            PileProvider::callback = [&]{ SetActiveConstellation(config.lastActiveConstellation); };
        }
        else SetActiveConstellation(config.lastActiveConstellation);
    }

    void PillowManager::LoadConstellations()
    {
        constellations = Constellation::ConstellationsFromFolderPath(CONSTELLATIONPATH);
    }

    Transform* PillowManager::SpawnPile(pillowparams param)
    {
        Pile* pile = PileProvider::GetPile(param.type);
        if (!pile) return nullptr;
        Transform* pileTransform = pile->get_transform();
        pileTransform->set_localPosition(param.position);
        pileTransform->set_localEulerAngles(param.rotation);
        return pileTransform;
    }

    void PillowManager::RemoveLastPillow()
    {
        int childCount = get_transform()->get_childCount();

        Object::Destroy(get_transform()->GetChild(childCount - 1));
    }

    void PillowManager::SetActiveConstellation(std::string name)
    {
        // find the constellation with this name, and then make that the active one
        Constellation* constellation = nullptr;
        if (name == "") name = "simple"; 

        for (auto& it : constellations)
        {
            if (it.get_name() == name) 
            {
                SetActiveConstellation(it);
                return;
            } 
        }
    }

    void PillowManager::SetActiveConstellation(Constellation constellation)
    {
        config.lastActiveConstellation = constellation.get_name();
        if (!config.enabled)
        {
            savedConstellation = constellation;
            useSaved = true;
            return;
        }

        // remove all old piles
        Array<Pile*>* piles = GetComponentsInChildren<Pile*>();
        if (piles)
        {
            for (int i = 0; i < piles->Length(); i++)
            {
                Pile* pile = piles->values[i];
                if (!pile) continue;
                Object::Destroy(pile->get_gameObject());
            }
        }

        // spawn all new piles
        const std::vector<pillowparams>& params = constellation.get_params();

        for (auto param : params)
        {
            Transform* pile = SpawnPile(param);
            if (pile) pile->SetParent(get_transform());
        }
    }

    std::vector<MenuPillow::Constellation>* PillowManager::GetConstellations()
    {
        PillowManager* manager = Object::FindObjectOfType<PillowManager*>();
        if (manager) return &manager->constellations;
        return nullptr;
    }

    void PillowManager::RandomizeTextures()
    {
        PillowManager* manager = Object::FindObjectOfType<PillowManager*>();
        if (!manager) return;
        if (!config.enabled)
        {
            manager->shouldRandomizeOnReEnable = true;
            return;
        }

        Array<Pile*>* piles = manager->GetComponentsInChildren<Pile*>(true);

        if (!piles) return;
        for (int i = 0; i < piles->Length(); i++)
        {
            Pile* pile = piles->values[i];
            if (!pile) continue;
            pile->RandomizeTextures();
        }
    }

    void PillowManager::OnModEnable()
    {
        PillowManager* manager = Object::FindObjectOfType<PillowManager*>();
        if (!manager) return;
        if (manager->useSaved)
        {
            manager->useSaved = false;
            manager->SetActiveConstellation(manager->savedConstellation);
        }
        else
        {
            int childCount = manager->get_transform()->get_childCount();
            for (int i = 0; i < childCount; i++)
            {
                Transform* child = manager->get_transform()->GetChild(i);
                child->get_gameObject()->SetActive(true);
            }
            if (manager->shouldRandomizeOnReEnable)
            {
                manager->shouldRandomizeOnReEnable = false;
                manager->RandomizeTextures();
            }
        }
    }

    void PillowManager::OnModDisable()
    {
        PillowManager* manager = Object::FindObjectOfType<PillowManager*>();
        if (!manager) return;
        int childCount = manager->get_transform()->get_childCount();
        for (int i = 0; i < childCount; i++)
        {
            Transform* child = manager->get_transform()->GetChild(i);
            child->get_gameObject()->SetActive(false);
        }
    }

    void PillowManager::OnDestroy()
    {
        getLogger().info("Pillow Manager destroyed!");
    }
}