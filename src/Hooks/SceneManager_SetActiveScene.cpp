#include "hooking.hpp"
#include "logging.hpp"
#include "config.hpp"

#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"

#include "CustomTypes/PillowManager.hpp"

using namespace CustomPillows;

void Show(bool doShow = true) {
    //PillowManager::get_instance()->Show(doShow);
}

void Hide(bool doHide = true) {
    //PillowManager::get_instance()->Hide(doHide);
}

bool inMulti = false;

MAKE_AUTO_HOOK_MATCH(SceneManager_SetActiveScene, &UnityEngine::SceneManagement::SceneManager::SetActiveScene, bool, UnityEngine::SceneManagement::Scene scene)
{
    auto result = SceneManager_SetActiveScene(scene);
    
    auto sceneName = scene.get_name();

    // in the main menu, show if enabled
    if (sceneName == "MainMenu") {
        if (inMulti) {
            Show(config.enabled && config.keepInMulti);
        } else {
            Show(config.enabled);
        }
    }
    
    // in level, show if enabled and keep in level is true
    if (sceneName == "GameCore") {
        if (inMulti) {
            Show(config.enabled && config.keepInLevel && config.keepInMulti);
        } else {
            Show(config.enabled && config.keepInLevel);
        }
    }

    return result;
}