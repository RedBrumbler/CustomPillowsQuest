#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "custom-types/shared/register.hpp"
#include "custom-types/shared/macros.hpp"

#include "Pillow.hpp"
#include "PillowManager.hpp"
#include "PileProvider.hpp"
#include "Pile.hpp"
#include "Updater.hpp"

#include "UnityEngine/SceneManagement/Scene.hpp"

#include "questui/shared/QuestUI.hpp"

ModInfo modInfo;

bool getSceneName(UnityEngine::SceneManagement::Scene scene, std::string& output);
std::string activeSceneName = "";

Logger& getLogger()
{
    Logger* logger = new Logger(modInfo, LoggerOptions(false, true));

    return *logger;
}

bool firstWarmup = true;
MAKE_HOOK_OFFSETLESS(SceneManager_SetActiveScene, bool, UnityEngine::SceneManagement::Scene scene)
{
    getSceneName(scene, activeSceneName);

    if (firstWarmup && activeSceneName == "ShaderWarmup")
    {
        firstWarmup = false;
        PileProvider::LoadBundle();
    }

    if (activeSceneName == "HealthWarning")
    {
        PileProvider::LoadAssets();
    }

    if (activeSceneName == "MenuViewControllers" || activeSceneName == "MenuCore")
    {
        PillowManager::OnMenuSceneActive();
    }
    return SceneManager_SetActiveScene(scene);
}

extern "C" void setup(ModInfo info)
{
    info.id = ID;
    info.version = VERSION;

    modInfo = info;
}

extern "C" void load()
{
    il2cpp_functions::Init();
    QuestUI::Init();
    LoggerContextObject logger = getLogger().WithContext("load");

    INSTALL_HOOK_OFFSETLESS(logger, SceneManager_SetActiveScene, il2cpp_utils::FindMethodUnsafe("UnityEngine.SceneManagement", "SceneManager", "SetActiveScene", 1));
    
    custom_types::Register::RegisterTypes<MenuPillow::PillowManager, MenuPillow::Pillow, MenuPillow::PileProvider, MenuPillow::Updater, MenuPillow::Pile>();
}

bool getSceneName(UnityEngine::SceneManagement::Scene scene, std::string& output)
{
    LoggerContextObject logger = getLogger().WithContext("scene name");
    Il2CppString* csString = UnityEngine::SceneManagement::Scene::GetNameInternal(scene.m_Handle);
    RET_0_UNLESS(logger, csString);
    output = to_utf8(csstrtostr(csString));
    return true; 
}