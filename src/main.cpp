#include "hooking.hpp"
#include "logging.hpp"
#include "config.hpp"

#include "custom-types/shared/register.hpp"
#include "questui/shared/QuestUI.hpp"

#include "UI/PillowSettingsFlowCoordinator.hpp"

ModInfo modInfo {MOD_ID, VERSION};

extern "C" void setup(ModInfo& info) 
{
    info = modInfo;
    INFO("Setup complete");
}

extern "C" void load() 
{
    if (!LoadConfig())
        SaveConfig();
    
    custom_types::Register::AutoRegister();

    auto& logger = CustomPillows::Logging::getLogger();
    Hooks::InstallHooks(logger);

    srand(time(NULL));

    QuestUI::Register::RegisterAllModSettingsFlowCoordinator<CustomPillows::PillowSettingsFlowCoordinator*>(modInfo, "Custom Pillows");
    INFO("Load Complete");
} 
