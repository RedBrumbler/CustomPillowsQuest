#pragma once

#include "custom-types/shared/macros.hpp"
#include "HMUI/FlowCoordinator.hpp"
#include "custom-types/shared/macros.hpp"
#include "UI/ConfigViewController.hpp"
#include "UI/TextureSelectorViewController.hpp"

DECLARE_CLASS_CODEGEN(MenuPillow, MenuPillowFlowCoordinator, HMUI::FlowCoordinator,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD(void, BackButtonWasPressed, il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator", "BackButtonWasPressed", 1), HMUI::ViewController* topViewController);
    
    DECLARE_INSTANCE_FIELD_DEFAULT(MenuPillow::ConfigViewController*, configViewController, nullptr);
    DECLARE_INSTANCE_FIELD_DEFAULT(MenuPillow::TextureSelectorViewController*, textureSelectorViewController, nullptr);
)