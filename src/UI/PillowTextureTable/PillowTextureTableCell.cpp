#include "UI/PillowTextureTable/PillowTextureTableCell.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/SpriteMeshType.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector4.hpp"

#include "HMUI/Touchable.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"

DEFINE_TYPE(CustomPillows, PillowTextureTableCell);

using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace HMUI;
using namespace QuestUI::BeatSaberUI;

UnityEngine::Color highlightedColor         = UnityEngine::Color(0.0f, 0.0f, 0.5f, 0.8f); // dark blue
UnityEngine::Color idleColor                = UnityEngine::Color(0.0f, 0.0f, 0.0f, 0.8f); // black
UnityEngine::Color selectedColor            = UnityEngine::Color(0.3f, 0.3f, 0.5f, 0.8f); // lighter blue
UnityEngine::Color selectedHighlightedColor = UnityEngine::Color(0.5f, 0.5f, 0.5f, 0.8f); // white

VerticalLayoutGroup* CreateHost(Transform* parent, Vector2 anchoredPos, Vector2 size)
{
    VerticalLayoutGroup* group = CreateVerticalLayoutGroup(parent);
    group->get_rectTransform()->set_anchoredPosition(anchoredPos);

    LayoutElement* elem = group->GetComponent<LayoutElement*>();
    elem->set_preferredHeight(size.y);
    elem->set_preferredWidth(size.x);

    ContentSizeFitter* fitter = group->GetComponent<ContentSizeFitter*>();
    fitter->set_verticalFit(ContentSizeFitter::FitMode::PreferredSize);
    fitter->set_horizontalFit(ContentSizeFitter::FitMode::PreferredSize);
    return group;
}

namespace CustomPillows {
    PillowTextureTableCell* PillowTextureTableCell::CreateNewCell() {
        static ConstString playerTableCellStr("PillowTextureTableCell");
        auto cellGO = GameObject::New_ctor();
        auto pillowTextureCell = cellGO->AddComponent<PillowTextureTableCell*>();
        cellGO->set_name(playerTableCellStr);
        pillowTextureCell->Setup();
        return pillowTextureCell;
    }

    void PillowTextureTableCell::Setup() {
        using Grass = HMUI::Touchable;
        // haha touch grass
        get_gameObject()->AddComponent<Grass*>();
        auto bgHost = CreateHost(get_transform(), {0.0f, 0.0}, {40.0f, 12.0f});
        auto bg = bgHost->get_gameObject()->AddComponent<QuestUI::Backgroundable*>();
        bg->ApplyBackgroundWithAlpha("title-gradient", 0.8f);

        background = bg->get_gameObject()->GetComponentInChildren<HMUI::ImageView*>();
        background->set_color(idleColor);
        background->set_color0({1.0f, 1.0f, 1.0f, 1.0f});
        background->set_color1({1.0f, 1.0f, 1.0f, 1.0f});

        auto imageHost = CreateHost(get_transform(), {-15.5f, 0}, {4.5f, 9.0f});
        textureImage = CreateImage(imageHost->get_transform(), nullptr, {0, 0}, {0, 0});
        textureImage->skew = 0.18f;

        auto textHost = CreateHost(get_transform(), {2.5f, 0.0}, {30.0f, 6.0f});
        textHost->set_childAlignment(UnityEngine::TextAnchor::MiddleLeft);
        textureName = CreateText(textHost->get_transform(), "---", {0, 0}, {0, 0});
        textureName->set_fontSize(4.0f);
        textureName->set_autoSizeTextContainer(true);
    }

    void PillowTextureTableCell::HighlightDidChange(HMUI::SelectableCell::TransitionType transitionType) {
        UpdateBackground();
    }

    void PillowTextureTableCell::SelectionDidChange(HMUI::SelectableCell::TransitionType transitionType) {
        UpdateBackground();
    }

    void PillowTextureTableCell::UpdateBackground() {
        if (!background) return;
        if (get_selected()) {
            background->set_color(get_highlighted() ? selectedHighlightedColor : selectedColor);
        } else {
            background->set_color(get_highlighted() ? highlightedColor : idleColor);
        }
    }

    void PillowTextureTableCell::SetText(StringW text) {
        if (!textureName) return;
        textureName->set_text(text);
    }

    void PillowTextureTableCell::SetTexture(UnityEngine::Texture2D* texture) {
        if (!textureImage){
            ERROR("textureImage was not set!");
            return;
        }
        if (!texture) {
            ERROR("texture was nullptr!");
            return;
        }
        auto sprite = Sprite::Create(texture, Rect(0.0f, 0.0f, (float)texture->get_width(), (float)texture->get_height()), Vector2(0.5f,0.5f), 1024.0f, 1u, SpriteMeshType::FullRect, Vector4(0.0f, 0.0f, 0.0f, 0.0f), false);
        SetTexture(sprite);
    }

    void PillowTextureTableCell::SetTexture(UnityEngine::Sprite* sprite) {
        if (!textureImage){
            ERROR("textureImage was not set!");
            return;
        }
        textureImage->set_sprite(sprite);
    }
}