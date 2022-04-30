#include "config.hpp"
#include "modloader/shared/modloader.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "custom-types/shared/register.hpp"

#include "CustomTypes/Pillow.hpp"
#include "CustomTypes/PillowManager.hpp"
#include "CustomTypes/PileProvider.hpp"
#include "CustomTypes/Pile.hpp"
#include "CustomTypes/Updater.hpp"

#include "UI/MenuPillowFlowCoordinator.hpp"
#include "UI/ConfigViewController.hpp"
#include "UI/TextureSelectorViewController.hpp"

#include "TexturePool.hpp"
#include "FileUtils.hpp"

#include "UnityEngine/SceneManagement/Scene.hpp"

#include "questui/shared/QuestUI.hpp"

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

#include "UnityEngine/SceneManagement/SceneManager.hpp"

bool multi = false;
bool firstWarmup = true;

MAKE_HOOK_MATCH(SceneManager_SetActiveScene, &UnityEngine::SceneManagement::SceneManager::SetActiveScene, bool, UnityEngine::SceneManagement::Scene scene)
{
    getSceneName(scene, activeSceneName);

    if (activeSceneName == "HealthWarning")
    {
        // get all tex names
        //TexturePool::LoadAllTextures();
        //PillowManager::LoadConstellations();
        // load bundle & assets right in one go
    }

    if (!multi && activeSceneName == "MainMenu")
    {
        PillowManager::OnMenuSceneActivate();
    }

    if (activeSceneName == "GameCore") PillowManager::OnMenuSceneDeActivate();

    getLogger().info("Found scene %s", activeSceneName.c_str());
    return SceneManager_SetActiveScene(scene);
}

MAKE_HOOK_MATCH(MainFlowCoordinator_DidActivate, &GlobalNamespace::MainFlowCoordinator::DidActivate, void, GlobalNamespace::MainFlowCoordinator* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    MainFlowCoordinator_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    if (firstActivation)
    {
        TexturePool::LoadAllTextures();
        PillowManager::LoadConstellations();

        UnityEngine::GameObject* newObj = UnityEngine::GameObject::New_ctor<il2cpp_utils::CreationType::Manual>();
        UnityEngine::Object::DontDestroyOnLoad(newObj);
        newObj->AddComponent<PillowManager*>();
    }
}

extern "C" void setup(ModInfo info)
{
    info.id = MOD_ID;
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

    //CopyDefaults();

    LoggerContextObject logger = getLogger().WithContext("load");
    logger.info("Installing Hooks...");

    // installing hooks
    INSTALL_HOOK(logger, SceneManager_SetActiveScene);
    INSTALL_HOOK(logger, MainFlowCoordinator_DidActivate);

    logger.info("Installed Hooks!");

    logger.info("Registering Types...");

    // register custom types
    custom_types::Register::AutoRegister();

    logger.info("Registered Types!");

    logger.info("Registering Flow Coordinator...");

    QuestUI::Register::RegisterModSettingsFlowCoordinator<MenuPillow::MenuPillowFlowCoordinator*>((ModInfo){"Custom Pillows", MOD_ID});

    logger.info("Registered Flow Coordinator!");
}

bool getSceneName(UnityEngine::SceneManagement::Scene scene, std::string& output)
{
    LoggerContextObject logger = getLogger().WithContext("scene name");
    StringW csString = UnityEngine::SceneManagement::Scene::GetNameInternal(scene.m_Handle);
    RET_0_UNLESS(logger, csString);
    output = static_cast<std::string>(csString);
    return true; 
}