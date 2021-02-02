#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "custom-types/shared/register.hpp"
#include "custom-types/shared/macros.hpp"

#include "CustomTypes/Pillow.hpp"
#include "CustomTypes/PillowManager.hpp"
#include "CustomTypes/PileProvider.hpp"
#include "CustomTypes/Pile.hpp"
#include "CustomTypes/Updater.hpp"

#include "UI/MenuPillowFlowCoordinator.hpp"
#include "UI/ConfigViewController.hpp"
#include "UI/TextureSelectorViewController.hpp"

#include "TexturePool.hpp"
#include "config.hpp"
#include "FileUtils.hpp"

#include "UnityEngine/SceneManagement/Scene.hpp"

#include "questui/shared/QuestUI.hpp"

#include "bs-utils/shared/utils.hpp"

#include "static-defines.hpp"
#include "GlobalNamespace/MainFlowCoordinator.hpp"


ModInfo modInfo;

bool getSceneName(UnityEngine::SceneManagement::Scene scene, std::string& output);
std::string activeSceneName = "";

using namespace MenuPillow;

Logger& getLogger()
{
    Logger* logger = new Logger(modInfo, LoggerOptions(false, true));

    return *logger;
}

void makeFolder(std::string directory)
{
    if (!direxists(directory.c_str()))
    {
        int makePath = mkpath(directory.data());
        if (makePath == -1)
        {
            getLogger().debug("Failed to make path %s", directory.c_str());
        }
    }
}
bool multi = false;
bool firstWarmup = true;
MAKE_HOOK_OFFSETLESS(SceneManager_SetActiveScene, bool, UnityEngine::SceneManagement::Scene scene)
{
    getSceneName(scene, activeSceneName);

    if (activeSceneName == "HealthWarning")
    {
        // get all tex names
        TexturePool::LoadAllTextures();
        PillowManager::LoadConstellations();
        // load bundle & assets right in one go
    }

    if (!multi && (activeSceneName == "MenuViewControllers" || activeSceneName == "MenuCore"))
    {
        PillowManager::OnMenuSceneActivate();
    }

    if (activeSceneName == "GameCore") PillowManager::OnMenuSceneDeActivate();

    getLogger().info("Found scene %s", activeSceneName.c_str());
    return SceneManager_SetActiveScene(scene);
}

MAKE_HOOK_OFFSETLESS(MainFlowCoordinator_DidActivate, void, GlobalNamespace::MainFlowCoordinator* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    MainFlowCoordinator_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    PillowManager* manager = UnityEngine::Object::FindObjectOfType<PillowManager*>();
    if (manager) return;
    
    UnityEngine::GameObject* newObj = UnityEngine::GameObject::New_ctor<il2cpp_utils::CreationType::Manual>();
    UnityEngine::Object::DontDestroyOnLoad(newObj);
    manager = newObj->AddComponent<PillowManager*>();
}

extern "C" void setup(ModInfo info)
{
    info.id = ID;
    info.version = VERSION;

    modInfo = info;

    getLogger().info("These pillows do be sexy tho");
}

extern "C" void load()
{
    il2cpp_functions::Init();
    QuestUI::Init();

    if (!LoadConfig()) 
            SaveConfig();
    std::string datapath = bs_utils::getDataDir(modInfo);

    //CopyDefaults();

    LoggerContextObject logger = getLogger().WithContext("load");
    logger.info("Installing Hooks...");

    // installing hooks
    INSTALL_HOOK_OFFSETLESS(logger, SceneManager_SetActiveScene, il2cpp_utils::FindMethodUnsafe("UnityEngine.SceneManagement", "SceneManager", "SetActiveScene", 1));
    INSTALL_HOOK_OFFSETLESS(logger, MainFlowCoordinator_DidActivate, il2cpp_utils::FindMethodUnsafe("", "MainFlowCoordinator", "DidActivate", 3));

    logger.info("Installed Hooks!");

    logger.info("Registering Types...");

    // register custom types
    custom_types::Register::RegisterTypes<MenuPillow::Pillow, MenuPillow::Updater, MenuPillow::Pile>();
    custom_types::Register::RegisterTypes<MenuPillow::PillowManager, MenuPillow::PileProvider>();
    custom_types::Register::RegisterTypes<MenuPillow::MenuPillowFlowCoordinator, MenuPillow::ConfigViewController, MenuPillow::TextureSelectorViewController>();

    logger.info("Registered Types!");

    logger.info("Registering Flow Coordinator...");

    QuestUI::Register::RegisterModSettingsFlowCoordinator<MenuPillow::MenuPillowFlowCoordinator*>((ModInfo){"Custom Pillows", ID});

    logger.info("Registered Flow Coordinator!");
}



bool getSceneName(UnityEngine::SceneManagement::Scene scene, std::string& output)
{
    LoggerContextObject logger = getLogger().WithContext("scene name");
    Il2CppString* csString = UnityEngine::SceneManagement::Scene::GetNameInternal(scene.m_Handle);
    RET_0_UNLESS(logger, csString);
    output = to_utf8(csstrtostr(csString));
    return true; 
}