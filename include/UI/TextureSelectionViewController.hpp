#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "bsml/shared/macros.hpp"
#include "HMUI/ViewController.hpp"

#include "CustomTypes/TexturePool.hpp"
#include "CustomTypes/PillowManagers/GlobalPillowManager.hpp"

#include "bsml/shared/BSML/Components/CustomListTableData.hpp"

DECLARE_CLASS_CODEGEN(CustomPillows, TextureSelectionViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(TexturePool*, texturePool);
    DECLARE_INSTANCE_FIELD(GlobalPillowManager*, globalPillowManager);
    DECLARE_INSTANCE_FIELD(BSML::CustomListTableData*, inactiveList);
    DECLARE_INSTANCE_FIELD(BSML::CustomListTableData*, activeList);

    DECLARE_INSTANCE_FIELD(ListWrapper<BSML::CustomCellInfo*>, _activeTextures);
    DECLARE_INSTANCE_FIELD(ListWrapper<BSML::CustomCellInfo*>, _inactiveTextures);
    
    DECLARE_INSTANCE_METHOD(ListWrapper<BSML::CustomCellInfo*>, get_activeTextures);
    DECLARE_INSTANCE_METHOD(ListWrapper<BSML::CustomCellInfo*>, get_inactiveTextures);

    DECLARE_INSTANCE_METHOD(void, ActivateSelected);
    DECLARE_INSTANCE_METHOD(void, DeActivateSelected);
    DECLARE_INSTANCE_METHOD(void, ReloadTextureLists);
    DECLARE_INSTANCE_METHOD(int, GetSelectedIdx, HMUI::TableView* tableView);
    DECLARE_INJECT_METHOD(void, Inject, TexturePool* texturePool, GlobalPillowManager* globalPillowManager);
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    
)