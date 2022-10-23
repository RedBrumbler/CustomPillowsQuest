#include "Installers/AppInstaller.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"
#include "Zenject/ConcreteIdBinderGeneric_1.hpp"

#include "CustomTypes/AssetManager.hpp"
#include "CustomTypes/PillowManager.hpp"
#include "CustomTypes/TexturePool.hpp"

DEFINE_TYPE(CustomPillows, AppInstaller);

namespace CustomPillows {
    void AppInstaller::InstallBindings() {
        INFO("Installing bindings!");
        auto container = get_Container();

        container->Bind<TexturePool*>()->AsSingle();
        auto go = UnityEngine::GameObject::New_ctor("AssetManager");
        UnityEngine::Object::DontDestroyOnLoad(go);
        container->BindInterfacesAndSelfTo<CustomPillows::AssetManager*>()->FromNewComponentOn(go)->AsSingle();
        go = UnityEngine::GameObject::New_ctor("PillowManager");
        UnityEngine::Object::DontDestroyOnLoad(go);
        container->BindInterfacesAndSelfTo<CustomPillows::PillowManager*>()->FromNewComponentOn(go)->AsSingle();
    }
}