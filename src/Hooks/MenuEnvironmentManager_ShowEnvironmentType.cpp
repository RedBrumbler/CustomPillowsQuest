#include "hooking.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "GlobalNamespace/MenuEnvironmentManager.hpp"

using MenuEnvironmentType = GlobalNamespace::MenuEnvironmentManager::MenuEnvironmentType;

extern void Show(bool doShow = true);
extern void Hide(bool doHide = true);

extern bool inMulti;

MAKE_AUTO_HOOK_MATCH(MenuEnvironmentManager_ShowEnvironmentType, &GlobalNamespace::MenuEnvironmentManager::ShowEnvironmentType, void, GlobalNamespace::MenuEnvironmentManager* self, GlobalNamespace::MenuEnvironmentManager::MenuEnvironmentType menuEnvironmentType)
{
    MenuEnvironmentManager_ShowEnvironmentType(self, menuEnvironmentType);

    switch (menuEnvironmentType) {
        case MenuEnvironmentType::None:
            break;
        case MenuEnvironmentType::Default:
            inMulti = false;
            Show(config.enabled);
            break;
        case MenuEnvironmentType::Lobby:
            inMulti = true;
            Show(config.enabled && config.keepInMulti);
            break;
        default:
            break;
    }
}
