#include "hooking.hpp"

#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "System/Action_1.hpp"
#include "Zenject/DiContainer.hpp"

#include "CustomTypes/AssetManager.hpp"
#include "CustomTypes/PillowManager.hpp"

using namespace CustomPillows;

MAKE_AUTO_HOOK_MATCH(MenuTransitionsHelper_RestartGame, &GlobalNamespace::MenuTransitionsHelper::RestartGame, void, GlobalNamespace::MenuTransitionsHelper* self, System::Action_1<Zenject::DiContainer*>* finishCallback)
{
    AssetManager::get_instance()->OnGameRestart();
    PillowManager::get_instance()->OnGameRestart();
    
    MenuTransitionsHelper_RestartGame(self, finishCallback);
}