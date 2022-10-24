#include "hooking.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "GlobalNamespace/MenuEnvironmentManager.hpp"
#include "UnityEngine/Resources.hpp"
#include "CustomTypes/PillowManagers/GlobalPillowManager.hpp"

using MenuEnvironmentType = GlobalNamespace::MenuEnvironmentManager::MenuEnvironmentType;

/*
void Show(bool doShow = true) {
    static SafePtrUnity<CustomPillows::GlobalPillowManager> manager;
    if (!manager) {
        manager = UnityEngine::Resources::FindObjectsOfTypeAll<CustomPillows::GlobalPillowManager*>().FirstOrDefault();
    }
    manager->Show(doShow);
}

UnorderedEventCallback<void> menuEnvironmentChanged;

MAKE_AUTO_HOOK_MATCH(MenuEnvironmentManager_ShowEnvironmentType, &GlobalNamespace::MenuEnvironmentManager::ShowEnvironmentType, void, GlobalNamespace::MenuEnvironmentManager* self, GlobalNamespace::MenuEnvironmentManager::MenuEnvironmentType menuEnvironmentType) {
    MenuEnvironmentManager_ShowEnvironmentType(self, menuEnvironmentType);
    switch (menuEnvironmentType) {
        case MenuEnvironmentType::None:
            break;
        case MenuEnvironmentType::Default:
            Show(config.enabled);
            break;
        case MenuEnvironmentType::Lobby:
            Show(config.enabled && config.keepInMulti);
            break;
        default:
            break;
    }
}
*/
