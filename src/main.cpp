#include "hooking.hpp"
#include "logging.hpp"
#include "config.hpp"
#include "assets.hpp"

#include "custom-types/shared/register.hpp"
#include "bsml/shared/BSMLDataCache.hpp"

#include "UI/PillowSettingsFlowCoordinator.hpp"
#include "UI/PillowSettingsGameplaySetupView.hpp"

#include "GlobalNamespace/MultiplayerMenuInstaller.hpp"

#include "Installers/AppInstaller.hpp"
#include "Installers/GameInstaller.hpp"
#include "Installers/MenuInstaller.hpp"
#include "Installers/MultiplayerMenuInstaller.hpp"

#include "lapiz/shared/zenject/Zenjector.hpp"

#include "static-defines.hpp"

ModInfo modInfo {MOD_ID, VERSION};

extern "C" void setup(ModInfo& info)
{
    info = modInfo;
    INFO("Setup complete");
}

extern "C" void load()
{
    mkpath(IMAGEPATH);
    mkpath(CONSTELLATIONPATH);

    if (!LoadConfig())
        SaveConfig();

    custom_types::Register::AutoRegister();

    auto& logger = CustomPillows::Logging::getLogger();
    Hooks::InstallHooks(logger);

    srand(time(NULL));

    auto zenjector = Lapiz::Zenject::Zenjector::Get();

    zenjector->Install<CustomPillows::AppInstaller*>(Lapiz::Zenject::Location::App);
    zenjector->Install<CustomPillows::GameInstaller*>(Lapiz::Zenject::Location::Player);
    zenjector->Install<CustomPillows::MenuInstaller*>(Lapiz::Zenject::Location::Menu);
    zenjector->Install<CustomPillows::MultiplayerMenuInstaller*, GlobalNamespace::MultiplayerMenuInstaller*>();
    INFO("Load Complete");
}

BSML_DATACACHE(arrow) {
    return IncludedAssets::arrow_png;
}

BSML_DATACACHE(gameplaySetupTab) {
    return IncludedAssets::GameplaySetupView_bsml;
}

