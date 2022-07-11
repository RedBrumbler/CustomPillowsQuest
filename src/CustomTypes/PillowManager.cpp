#include "CustomTypes/PillowManager.hpp"
#include "static-defines.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "UnityEngine/Transform.hpp"
#include <fmt/core.h>

DEFINE_TYPE(CustomPillows, PillowManager);

using namespace UnityEngine;

namespace CustomPillows {
    PillowManager* PillowManager::instance = nullptr;

    void PillowManager::ctor() {
        currentPiles = List<Pile*>::New_ctor();
        currentConstellation = Constellation();
        constellations = {};
    }

    PillowManager* PillowManager::get_instance() {
        if (instance) return instance;
            static ConstString pillowModelManager{"PillowModelManager"};
            auto go = GameObject::New_ctor(pillowModelManager);
            Object::DontDestroyOnLoad(go);
            instance = go->AddComponent<PillowManager*>();
            return instance;
    }

    void PillowManager::OnGameRestart() {
        instance = nullptr;
        Object::DestroyImmediate(this->get_gameObject());
    }

    void PillowManager::PostPillowLoad() {
        // instantiate pillows n stuff
        constellations = Constellation::ConstellationsFromFolderPath(CONSTELLATIONPATH);
        SetConstellation(config.lastActiveConstellation);

        // if not enabled, hide everything
        Show(config.enabled);
    }

    void PillowManager::SetConstellation(int index) {
        SetConstellation(constellations[index % constellations.size()]);
    }

    void PillowManager::SetConstellation(std::string_view name) {
        auto itr = std::find_if(constellations.begin(), constellations.end(), [name](auto& x) -> bool {
            return x.get_name() == name;
        });

        if (itr != constellations.end()) {
            DEBUG("Found Constellation!");
            SetConstellation(*itr);
        } else {
            ERROR("Could not find the constellation named {}, not changing", name);
        }
    }
    

    void PillowManager::SetConstellation(const Constellation& constellation) {
        DEBUG("Checking Equivalency between constellations");
        if (currentConstellation.get_name() == constellation.get_name()) return;
        
        // remove old piles
        DEBUG("Removing old piles");
        for (auto pile : currentPiles) {
            Object::DestroyImmediate(pile->get_gameObject());
        }
        currentPiles->Clear();

        // save constellation
        DEBUG("Saving constellation");
        currentConstellation = constellation;
        
        // create new piles
        DEBUG("Get parent transform");
        auto parent = get_transform();

        DEBUG("Creating new piles");
        for (const auto& params : constellation.get_params()) {
            auto pile = assetManager->GetPile(params.type);
            auto transform = pile->get_transform();
            transform->SetParent(parent, false);
            transform->set_position(params.position);
            transform->set_eulerAngles(params.rotation);
            transform->set_localScale({0.4f, 0.4f, 0.4f});

            currentPiles->Add(pile);
        }
    }
    
    void PillowManager::Hide(bool doHide) {
        if (!currentPiles) return;
        for (auto pile : currentPiles) {
            pile->Hide(doHide);
        }
    }

    void PillowManager::Show(bool doShow) {
        Hide(!doShow);
    }

    void PillowManager::Shuffle() {
        for (auto pile : currentPiles) {
            pile->Shuffle();
        }
    }

    std::vector<std::string> PillowManager::get_constellationNames() {
        std::vector<std::string> names;
        names.reserve(constellations.size());
        for (auto& constellation : constellations) {
            names.emplace_back(constellation.get_name());
        }
        return names;
    }
}