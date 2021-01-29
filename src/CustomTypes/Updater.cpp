#include "CustomTypes/Updater.hpp"
#include "CustomTypes/PileProvider.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Object.hpp"

DEFINE_CLASS(MenuPillow::Updater);

using namespace UnityEngine;

void MenuPillow::Updater::Update()
{
    PileProvider::ManualUpdate();
}

void MenuPillow::Updater::Construct()
{
    GameObject* obj = GameObject::New_ctor();
    Object::DontDestroyOnLoad(obj);
    obj->AddComponent<Updater*>();
}

void MenuPillow::Updater::doDestroy()
{
    Updater* obj = Object::FindObjectOfType<Updater*>();
    Object::Destroy(obj);
}