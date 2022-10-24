#include "UI/TextureSelectionViewController.hpp"
#include "config.hpp"
#include "logging.hpp"
#include "assets.hpp"

#include "System/Collections/Generic/HashSet_1.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/Helpers/utilities.hpp"

DEFINE_TYPE(CustomPillows, TextureSelectionViewController);

using namespace UnityEngine;
using namespace UnityEngine::UI;

namespace CustomPillows {
    void TextureSelectionViewController::Inject(TexturePool* texturePool, GlobalPillowManager* globalPillowManager) {
        this->texturePool = texturePool;
        this->globalPillowManager = globalPillowManager;
    }

    void TextureSelectionViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (firstActivation) {
            auto activeTextureList = get_activeTextures();
            auto inactiveTextureList = get_inactiveTextures();

            for(const auto& activePair : texturePool->activeTexturesArray) {
                activeTextureList->Add(BSML::CustomCellInfo::construct(activePair.key, nullptr, BSML::Utilities::LoadSpriteFromTexture(activePair.value)));
            }

            for(const auto& inactivePair : texturePool->inActiveTexturesArray) {
                inactiveTextureList->Add(BSML::CustomCellInfo::construct(inactivePair.key, nullptr, BSML::Utilities::LoadSpriteFromTexture(inactivePair.value)));
            }

            BSML::parse_and_construct(IncludedAssets::TextureSelectView_bsml, get_transform(), this);
            ReloadTextureLists();
        }
    }

    int TextureSelectionViewController::GetSelectedIdx(HMUI::TableView* tableView) {
        if (tableView->selectedCellIdxs->get_Count() <= 0) return -1;
        
        auto enumerator = tableView->selectedCellIdxs->GetEnumerator();
        if (!enumerator.MoveNext()) return -1;
        int temp = enumerator.current;
        enumerator.Dispose();
        return temp;
    }

    void TextureSelectionViewController::ActivateSelected() {
        INFO("Activating texture");
        int selectedIndex = GetSelectedIdx(inactiveList->tableView);
        if (selectedIndex < 0) return;

        auto activeTextureList = get_activeTextures();
        auto inactiveTextureList = get_inactiveTextures();

        auto entry = inactiveTextureList[selectedIndex];
        auto name = entry->text;
        
        //swap em
        activeTextureList->Add(entry);
        inactiveTextureList->Remove(entry);

        texturePool->ActivateTexture(name);
        DEBUG("Adding {} to config", static_cast<std::string>(name));
        config.lastActiveTextures.push_back(name);
        SaveConfig();

        ReloadTextureLists();
        globalPillowManager->Shuffle();
    }

    void TextureSelectionViewController::DeActivateSelected() {
        INFO("Deactivating texture");
        int selectedIndex = GetSelectedIdx(activeList->tableView);
        if (selectedIndex < 0) return;
        
        auto activeTextureList = get_activeTextures();
        auto inactiveTextureList = get_inactiveTextures();

        auto entry = activeTextureList[selectedIndex];
        auto name = entry->text;
        
        //swap em
        inactiveTextureList->Add(entry);
        activeTextureList->Remove(entry);

        texturePool->DeactivateTexture(name);

        auto itr = std::find(config.lastActiveTextures.begin(), config.lastActiveTextures.end(), name);
        DEBUG("Removing {} from config", static_cast<std::string>(name));
        config.lastActiveTextures.erase(itr, itr + 1);
        SaveConfig();

        ReloadTextureLists();
        globalPillowManager->Shuffle();
    }

    ListWrapper<BSML::CustomCellInfo*> TextureSelectionViewController::get_activeTextures() {
        if (!_activeTextures) {
            _activeTextures = List<BSML::CustomCellInfo*>::New_ctor();
        }
        return _activeTextures;
    }

    ListWrapper<BSML::CustomCellInfo*> TextureSelectionViewController::get_inactiveTextures() {
        if (!_inactiveTextures) {
            _inactiveTextures = List<BSML::CustomCellInfo*>::New_ctor();
        }
        return _inactiveTextures;
    }

    void TextureSelectionViewController::ReloadTextureLists() {
        INFO("Reloading texture lists");
        DEBUG("Inactive");
        inactiveList->tableView->ClearSelection();
        inactiveList->tableView->ReloadDataKeepingPosition();

        DEBUG("Active");
        activeList->tableView->ClearSelection();
        activeList->tableView->ReloadDataKeepingPosition();

        DEBUG("Reloaded texture lists");
    }
}