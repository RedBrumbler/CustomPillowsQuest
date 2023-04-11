#include "Installers/AppInstaller.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"
#include "Zenject/ConcreteIdBinderGeneric_1.hpp"

#include "CustomTypes/AssetManager.hpp"
#include "CustomTypes/PillowManagers/GlobalPillowManager.hpp"
#include "CustomTypes/TexturePool.hpp"

#include "lapiz/shared/utilities/ZenjectExtensions.hpp"
DEFINE_TYPE(CustomPillows, AppInstaller);

using namespace Lapiz::Zenject::ZenjectExtensions;
namespace CustomPillows {
    void AppInstaller::InstallBindings() {
        INFO("Installing bindings!");
        auto container = get_Container();

        container->BindInterfacesAndSelfTo<TexturePool*>()->AsSingle();

        auto params = ::Zenject::GameObjectCreationParameters::New_ctor();
        params->set_Name("AssetManager");
        FromNewComponentOnNewGameObject(container->BindInterfacesAndSelfTo<CustomPillows::AssetManager*>(), params)->AsSingle();

        auto params2 = ::Zenject::GameObjectCreationParameters::New_ctor();
        params2->set_Name("GlobalPillowManager");
        FromNewComponentOnNewGameObject(container->BindInterfacesAndSelfTo<CustomPillows::GlobalPillowManager*>(), params2)->AsSingle();
    }
}