#pragma once

#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "HMUI/TableCell.hpp"
#include "HMUI/TableView.hpp"
#include "HMUI/TableView_IDataSource.hpp"

#include "CustomTypes/TexturePool.hpp"

#ifndef DECLARE_OVERRIDE_METHOD_MATCH
#define DECLARE_OVERRIDE_METHOD_MATCH(retval, method, mptr, ...) \
    DECLARE_OVERRIDE_METHOD(retval, method, il2cpp_utils::il2cpp_type_check::MetadataGetter<mptr>::get(), __VA_ARGS__)
#endif

___DECLARE_TYPE_WRAPPER_INHERITANCE(CustomPillows, PillowTextureTableData, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, UnityEngine::MonoBehaviour, "CustomPillows", {classof(HMUI::TableView::IDataSource*)}, 0, nullptr,
    DECLARE_INSTANCE_FIELD(StringW, reuseIdentifier);
    DECLARE_INSTANCE_FIELD(HMUI::TableView*, tableView);
    DECLARE_INSTANCE_FIELD(TexturePool*, texturePool);
    DECLARE_INSTANCE_FIELD(TexturePool::NameToTexture*, textures);
    DECLARE_INSTANCE_FIELD(ArrayW<TexturePool::NameToTexturePair>, texturePairs);

    DECLARE_CTOR(ctor);
    DECLARE_INSTANCE_METHOD(void, Start);

    DECLARE_OVERRIDE_METHOD_MATCH(HMUI::TableCell*, CellForIdx, &HMUI::TableView::IDataSource::CellForIdx, HMUI::TableView* tableView, int idx);
    DECLARE_OVERRIDE_METHOD_MATCH(float, CellSize, &HMUI::TableView::IDataSource::CellSize);
    DECLARE_OVERRIDE_METHOD_MATCH(int, NumberOfCells, &HMUI::TableView::IDataSource::NumberOfCells);
    public:
        constexpr static float cellSize = 12.0f;
)