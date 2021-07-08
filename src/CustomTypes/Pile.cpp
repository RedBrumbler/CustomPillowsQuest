#include "CustomTypes/Pile.hpp"
#include "UnityEngine/WaitUntil.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Coroutine.hpp"
#include "System/Collections/IEnumerator.hpp"
#include "System/Func_1.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "TexturePool.hpp"

#include "questui/shared/CustomTypes/Data/CustomDataType.hpp"

DEFINE_TYPE(MenuPillow, Pile);

static Il2CppString* meshName = nullptr;

using namespace UnityEngine;

struct PillowData {
    int count;
    Array<MenuPillow::Pillow*>* pillows;

    PillowData(int count, Array<MenuPillow::Pillow*>* pillows) : count(count), pillows(pillows) {};
};

namespace MenuPillow
{
    Array<Pillow*>* Pile::GetPillows()
    {
        return get_gameObject()->GetComponentsInChildren<Pillow*>(true);
    }

    void Pile::Awake()
    {
        childCount = get_transform()->get_childCount();
        if (!meshName) meshName = il2cpp_utils::createcsstr("mesh", il2cpp_utils::StringType::Manual);
        get_transform()->set_localScale(UnityEngine::Vector3::get_one() * 0.4f);
        StartCoroutine(reinterpret_cast<System::Collections::IEnumerator*>(custom_types::Helpers::CoroutineHelper::New(SetupPillowsRoutine())));
    }

    custom_types::Helpers::Coroutine Pile::SetupPillowsRoutine()
    {
        if (!meshName) meshName = il2cpp_utils::createcsstr("mesh", il2cpp_utils::StringType::Manual);

        int childCount = get_transform()->get_childCount();
        for (int i = 0; i < childCount; i++)
        {
            Transform* child = get_transform()->GetChild(i);
            Transform* mesh = child->Find(meshName);
            if (!mesh->get_gameObject()->GetComponent<Pillow*>()) mesh->get_gameObject()->AddComponent<Pillow*>();
            co_yield nullptr;
        }

        co_return;
    }

    void Pile::Update()
    {
        if (randomizeTextures)
        {
            randomizeTextures = false;
            RandomizeTextures();
        }
    }

    void Pile::RandomizeTextures()
    {
        Array<Pillow*>* pillows = GetPillows();
        PillowData* data = new PillowData(pillows->Length(), pillows);
        StartCoroutine(reinterpret_cast<System::Collections::IEnumerator*>(custom_types::Helpers::CoroutineHelper::New(RandomizeRoutine(data))));
    }
    
    custom_types::Helpers::Coroutine Pile::RandomizeRoutine(PillowData* data)
    {
        for (int i = 0; i < data->count; i++)
        {
            std::string name = TexturePool::GetTextureName();
            Pillow* pillow = data->pillows->values[i];
            if (name != "" && pillow) pillow->InitFromName(name);
            co_yield nullptr;
        }

        free (data);
        co_return;
    }

}
