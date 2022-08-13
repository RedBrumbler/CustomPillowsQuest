#include "UI/TextureSelectionViewController.hpp"
#include "UI/PillowTextureTable/PillowTextureTableCell.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "CustomTypes/AssetManager.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/List/QuestUITableView.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

DEFINE_TYPE(CustomPillows, TextureSelectionViewController);

#define SetPreferredSize(identifier, width, height)                                         \
    auto layout##identifier = identifier->get_gameObject()->GetComponent<LayoutElement*>(); \
    if (!layout##identifier)                                                                \
        layout##identifier = identifier->get_gameObject()->AddComponent<LayoutElement*>();  \
    layout##identifier->set_preferredWidth(width);                                          \
    layout##identifier->set_preferredHeight(height);                                        \
    auto fitter##identifier = identifier->GetComponent<ContentSizeFitter*>();               \
    fitter##identifier->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);         \
    fitter##identifier->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize)

using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace QuestUI::BeatSaberUI;

namespace CustomPillows {
    void TextureSelectionViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        if (firstActivation) {
            auto vertical = CreateVerticalLayoutGroup(get_transform());
            auto horizontal = CreateHorizontalLayoutGroup(vertical);

            auto leftListVertical = CreateVerticalLayoutGroup(horizontal);
            auto leftListTextVertical = CreateVerticalLayoutGroup(leftListVertical);
            auto swapButtonsVertical = CreateVerticalLayoutGroup(horizontal);
            auto rightListVertical = CreateVerticalLayoutGroup(horizontal);
            auto rightListTextVertical = CreateVerticalLayoutGroup(rightListVertical);

            auto assetManager = AssetManager::get_instance();
            texturePool = assetManager->texturePool;
            pillowManager = PillowManager::get_instance();

            SetPreferredSize(vertical, 140.0f, 84.0f);
            SetPreferredSize(horizontal, 140.0f, 84.0f);
            SetPreferredSize(leftListVertical, 50.0f, 84.0f);
            SetPreferredSize(leftListTextVertical, 50.0f, 8.0f);
            SetPreferredSize(swapButtonsVertical, 30.0f, 30);
            SetPreferredSize(rightListVertical, 50.0f, 84.0f);
            SetPreferredSize(rightListTextVertical, 50.0f, 8.0f);

            leftListTextVertical->set_childAlignment(UnityEngine::TextAnchor::MiddleCenter);
            rightListTextVertical->set_childAlignment(UnityEngine::TextAnchor::MiddleCenter);
            auto leftTextBg = leftListTextVertical->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
            leftTextBg->ApplyBackgroundWithAlpha("round-rect-panel", 0.8f);

            auto rightTextBg = rightListTextVertical->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
            rightTextBg->ApplyBackgroundWithAlpha("round-rect-panel", 0.8f);

            vertical->set_spacing(10.0f);
            auto inactiveText = CreateText(leftListTextVertical, "Inactive");
            inactiveText->set_alignment(TMPro::TextAlignmentOptions::Center);
            inactiveText->set_fontSize(7.0f);
            inactiveList = CreateScrollableCustomSourceList<PillowTextureTableData*>(leftListVertical->get_transform(), {-5.0f, 0.0f}, {40.0f, 76.0f});
            inactiveList->textures = texturePool->inActiveTextures;
            inactiveList->texturePool = texturePool;

            CreateUIButton(swapButtonsVertical->get_transform(), "->", std::bind(&TextureSelectionViewController::ActivateSelected, this));
            CreateUIButton(swapButtonsVertical->get_transform(), "<-", std::bind(&TextureSelectionViewController::DeActivateSelected, this));

            auto activeText = CreateText(rightListTextVertical, "Active");
            activeText->set_alignment(TMPro::TextAlignmentOptions::Center);
            activeText->set_fontSize(7.0f);
            activeList = CreateScrollableCustomSourceList<PillowTextureTableData*>(rightListVertical->get_transform(), {5.0f, 0.0f}, {40.0f, 76.0f});
            activeList->textures = texturePool->activeTextures;
            activeList->texturePool = texturePool;
            ReloadTextureLists();
        }
    }

    void TextureSelectionViewController::ActivateSelected() {
        INFO("Activating texture");
        auto tableView = reinterpret_cast<QuestUI::TableView*>(inactiveList->tableView);
        auto selectedIndex = tableView->get_selectedRow();
        if (selectedIndex < 0) 
            return;
        auto entry = inactiveList->texturePairs[selectedIndex];
        auto name = entry.key;

        texturePool->ActivateTexture(name);
        DEBUG("Adding {} to config", static_cast<std::string>(name));
        config.lastActiveTextures.push_back(name);
        SaveConfig();

        ReloadTextureLists();
        pillowManager->Shuffle();
    }

    void TextureSelectionViewController::DeActivateSelected() {
        INFO("Deactivating texture");
        auto tableView = reinterpret_cast<QuestUI::TableView*>(activeList->tableView);
        auto selectedIndex = tableView->get_selectedRow();
        if (selectedIndex < 0) 
            return;
        auto entry = activeList->texturePairs[selectedIndex];
        auto name = entry.key;

        texturePool->DeactivateTexture(name);

        auto itr = std::find(config.lastActiveTextures.begin(), config.lastActiveTextures.end(), name);
        DEBUG("Removing {} from config", static_cast<std::string>(name));
        config.lastActiveTextures.erase(itr, itr + 1);
        SaveConfig();

        ReloadTextureLists();
        pillowManager->Shuffle();
    }

    void TextureSelectionViewController::ReloadTextureLists() {
        INFO("Reloading texture lists");
        DEBUG("Inactive");
        inactiveList->texturePairs = texturePool->inActiveTexturesArray;
        inactiveList->tableView->ReloadDataKeepingPosition();
        inactiveList->tableView->ClearSelection();

        DEBUG("Active");
        activeList->texturePairs = texturePool->activeTexturesArray;
        activeList->tableView->ReloadDataKeepingPosition();
        activeList->tableView->ClearSelection();

        DEBUG("Reloaded texture lists");
    }
}