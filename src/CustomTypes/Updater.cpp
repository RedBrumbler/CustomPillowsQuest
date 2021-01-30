#include "CustomTypes/Updater.hpp"
#include "CustomTypes/PileProvider.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Object.hpp"

DEFINE_CLASS(MenuPillow::Updater);

using namespace UnityEngine;

void MenuPillow::Updater::Update()
{
    // run the manual update method on the pile provider
    PileProvider::ManualUpdate();
}

void MenuPillow::Updater::Construct()
{
    // make an updater
    GameObject* obj = GameObject::New_ctor();
    Object::DontDestroyOnLoad(obj);
    obj->AddComponent<Updater*>();
}

void MenuPillow::Updater::doDestroy()
{
    // destroy an updater
    Updater* obj = Object::FindObjectOfType<Updater*>();
    Object::Destroy(obj);
}