#include "hooking.hpp"

#include "GlobalNamespace/MainFlowCoordinator.hpp"
#include "CustomTypes/AssetManager.hpp"
#include "CustomTypes/PillowManager.hpp"

using namespace CustomPillows;

MAKE_AUTO_HOOK_MATCH(MainFlowCoordinator_DidActivate, &GlobalNamespace::MainFlowCoordinator::DidActivate, void, GlobalNamespace::MainFlowCoordinator* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    MainFlowCoordinator_DidActivate(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    if (firstActivation)
    {
        auto assetManager = AssetManager::get_instance();
        auto pillowManager = PillowManager::get_instance();
        pillowManager->assetManager = assetManager;

        assetManager->StartCoroutine(custom_types::Helpers::CoroutineHelper::New(assetManager->LoadPillows(std::bind(&PillowManager::PostPillowLoad, pillowManager))));
    }
}