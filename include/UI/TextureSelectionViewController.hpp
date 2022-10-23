#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "HMUI/ViewController.hpp"

#include "UI/PillowTextureTable/PillowTextureTableData.hpp"
#include "CustomTypes/TexturePool.hpp"
#include "CustomTypes/PillowManager.hpp"

#ifndef DECLARE_OVERRIDE_METHOD_MATCH
#define DECLARE_OVERRIDE_METHOD_MATCH(retval, name, mptr, ...) \
    DECLARE_OVERRIDE_METHOD(retval, name, il2cpp_utils::il2cpp_type_check::MetadataGetter<mptr>::get(), __VA_ARGS__)
#endif

DECLARE_CLASS_CODEGEN(CustomPillows, TextureSelectionViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(TexturePool*, texturePool);
    DECLARE_INSTANCE_FIELD(PillowManager*, pillowManager);
    DECLARE_INSTANCE_FIELD(PillowTextureTableData*, inactiveList);
    DECLARE_INSTANCE_FIELD(PillowTextureTableData*, activeList);
    
    DECLARE_INJECT_METHOD(void, Inject, TexturePool* texturePool, PillowManager* pillowManager);
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    private:
        void ActivateSelected();
        void DeActivateSelected();
        void ReloadTextureLists();


)