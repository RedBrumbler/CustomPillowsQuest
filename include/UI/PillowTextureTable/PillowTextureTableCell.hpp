#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/TableCell.hpp"
#include "HMUI/ImageView.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Texture2D.hpp"

#ifndef DECLARE_OVERRIDE_METHOD_MATCH
#define DECLARE_OVERRIDE_METHOD_MATCH(retval, method, mptr, ...) \
    DECLARE_OVERRIDE_METHOD(retval, method, il2cpp_utils::il2cpp_type_check::MetadataGetter<mptr>::get(), __VA_ARGS__)
#endif

DECLARE_CLASS_CODEGEN(CustomPillows, PillowTextureTableCell, HMUI::TableCell,
        DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, textureName);
        DECLARE_INSTANCE_FIELD(HMUI::ImageView*, textureImage);
        DECLARE_INSTANCE_FIELD(HMUI::ImageView*, background);

        DECLARE_OVERRIDE_METHOD_MATCH(void, HighlightDidChange, &HMUI::SelectableCell::HighlightDidChange, HMUI::SelectableCell::TransitionType transitionType);
        DECLARE_OVERRIDE_METHOD_MATCH(void, SelectionDidChange, &HMUI::SelectableCell::SelectionDidChange, HMUI::SelectableCell::TransitionType transitionType);

    public:
        static PillowTextureTableCell* CreateNewCell();
        
        void UpdateBackground();
        void Setup();

        void SetText(StringW text);

        void SetTexture(UnityEngine::Texture2D* texture);
        void SetTexture(UnityEngine::Sprite* sprite);
)
