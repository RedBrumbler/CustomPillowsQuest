#include "CustomTypes/PillowManagers/GlobalPillowManager.hpp"
#include "static-defines.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "UnityEngine/Transform.hpp"
#include <fmt/core.h>

DEFINE_TYPE(CustomPillows, GlobalPillowManager);

using namespace UnityEngine;

namespace CustomPillows {

    void GlobalPillowManager::Inject(AssetManager* assetManager) {
        this->assetManager = assetManager;
    }

    void GlobalPillowManager::Initialize() {
        DEBUG("Initialize");
        assetManager->StartCoroutine(custom_types::Helpers::CoroutineHelper::New(assetManager->LoadPillows(std::bind(&GlobalPillowManager::PostPillowLoad, this))));
    }

    void GlobalPillowManager::ctor() {
        currentPiles = List<Pile*>::New_ctor();
        currentConstellation = Constellation();
        constellations = {};
    }

    void GlobalPillowManager::OnGameRestart() {
        
    }

    void GlobalPillowManager::PostPillowLoad() {
        // instantiate pillows n stuff
        constellations = Constellation::ConstellationsFromFolderPath(CONSTELLATIONPATH);
        SetConstellation(config.lastActiveConstellation);

        // if not enabled, hide everything
        Show(config.enabled);
    }

    void GlobalPillowManager::SetConstellation(int index) {
        SetConstellation(constellations[index % constellations.size()]);
    }

    void GlobalPillowManager::SetConstellation(std::string_view name) {
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
    

    void GlobalPillowManager::SetConstellation(const Constellation& constellation) {
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
    
    void GlobalPillowManager::Hide(bool doHide) {
        if (!currentPiles) return;
        for (auto pile : currentPiles) {
            pile->Hide(doHide);
        }
    }

    void GlobalPillowManager::Show(bool doShow) {
        Hide(!doShow);
    }

    void GlobalPillowManager::Shuffle() {
        for (auto pile : currentPiles) {
            pile->Shuffle();
        }
    }

    std::vector<std::string> GlobalPillowManager::get_constellationNames() {
        std::vector<std::string> names;
        names.reserve(constellations.size());
        for (auto& constellation : constellations) {
            names.emplace_back(constellation.get_name());
        }
        return names;
    }
}