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

bool firstWarmup = true;
MAKE_HOOK_OFFSETLESS(SceneManager_SetActiveScene, bool, UnityEngine::SceneManagement::Scene scene)
{
    getSceneName(scene, activeSceneName);

    if (firstWarmup && activeSceneName == "ShaderWarmup")
    {
        firstWarmup = false;
        //PileProvider::LoadBundle();
    }

    if (activeSceneName == "HealthWarning")
    {
        TexturePool::LoadAllTextures();
        
        PileProvider::LoadBundle(true);
    }

    if (activeSceneName == "MenuViewControllers" || activeSceneName == "MenuCore")
    {
        PillowManager::OnMenuSceneActivate();
    }
    else PillowManager::OnMenuSceneDeActivate();
    return SceneManager_SetActiveScene(scene);
}

void CopyDefaults()
{
    makeFolder(CONSTELLATIONPATH);
    makeFolder(IMAGEPATH);

    std::string constellationPath = CONSTELLATIONPATH;
    std::string imagePath = IMAGEPATH;
    std::vector<std::string> fileNames = {};
    getLogger().info("Possibly copying defaults from %s", MODPATH);
    if (FileUtils::getFileNamesInDir("png", MODPATH, fileNames))
    {
        for (auto name : fileNames)
        {
            if (name.find("cover") != std::string::npos) continue;
            std::string destination = imagePath + name;
            if (fileexists(destination.c_str())) continue;
            std::string source = MODPATH + name;
            getLogger().info("Copying %s to %s", source.c_str(), destination.c_str());
            writefile(destination.c_str(), readfile(source.c_str()));
        }
    }
    fileNames.clear();

    if (FileUtils::getFileNamesInDir("json", MODPATH, fileNames))
    {
        for (auto name : fileNames)
        {
            if (name.find("bmbfmod") != std::string::npos) continue;
            std::string destination = constellationPath + name;
            if (fileexists(destination.c_str())) continue;
            std::string source = MODPATH + name;
            getLogger().info("Copying %s to %s", source.c_str(), destination.c_str());
            writefile(destination.c_str(), readfile(source.c_str()));
        }

    }
    std::string source = string_format("%s%s", MODPATH, "container.pillows");
    if (!fileexists(PILLOWPATH)) writefile(PILLOWPATH, readfile(source));
    
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

    if (!LoadConfig()) 
            SaveConfig();
    std::string datapath = bs_utils::getDataDir(modInfo);

    CopyDefaults();

    LoggerContextObject logger = getLogger().WithContext("load");
    logger.info("Persistent data path: %s", datapath.c_str());
    INSTALL_HOOK_OFFSETLESS(logger, SceneManager_SetActiveScene, il2cpp_utils::FindMethodUnsafe("UnityEngine.SceneManagement", "SceneManager", "SetActiveScene", 1));
    custom_types::Register::RegisterTypes<MenuPillow::Pillow, MenuPillow::Updater, MenuPillow::Pile>();
    custom_types::Register::RegisterTypes<MenuPillow::PillowManager, MenuPillow::PileProvider>();
    custom_types::Register::RegisterTypes<MenuPillow::MenuPillowFlowCoordinator, MenuPillow::ConfigViewController, MenuPillow::TextureSelectorViewController>();

    QuestUI::Register::RegisterModSettingsFlowCoordinator<MenuPillow::MenuPillowFlowCoordinator*>((ModInfo){"Custom Pillows Quest", ID});
}

bool getSceneName(UnityEngine::SceneManagement::Scene scene, std::string& output)
{
    LoggerContextObject logger = getLogger().WithContext("scene name");
    Il2CppString* csString = UnityEngine::SceneManagement::Scene::GetNameInternal(scene.m_Handle);
    RET_0_UNLESS(logger, csString);
    output = to_utf8(csstrtostr(csString));
    return true; 
}