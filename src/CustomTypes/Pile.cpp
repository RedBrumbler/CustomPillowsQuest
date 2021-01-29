#include "CustomTypes/Pile.hpp"
#include "UnityEngine/WaitUntil.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Coroutine.hpp"
#include "System/Collections/IEnumerator.hpp"
#include "System/Func_1.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "TexturePool.hpp"

DEFINE_CLASS(MenuPillow::Pile);

static Il2CppString* meshName = nullptr;

using namespace UnityEngine;

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
        auto coroutine = WaitUntil::New_ctor(il2cpp_utils::MakeDelegate<System::Func_1<bool>*>(classof(System::Func_1<bool>*), this,
        +[](Pile* self){
            if (self->childIndex >= self->childCount)
            {
                return true;
            }
            self->get_transform()->set_localScale(UnityEngine::Vector3::get_one() * 0.5f);
            Transform* child = self->get_transform()->GetChild(self->childIndex);
            Transform* mesh = child->Find(meshName);
            if (!mesh->get_gameObject()->GetComponent<Pillow*>()) mesh->get_gameObject()->AddComponent<Pillow*>();
            self->childIndex++;
            return false;
        }));

        StartCoroutine(reinterpret_cast<System::Collections::IEnumerator*>(coroutine));
        RandomizeTextures();
    }

    void Pile::RandomizeTextures()
    {
        Array<Pillow*>* pillows = GetPillows();
        for (int i = 0; i < pillows->Length(); i++)
        {
            std::string name = TexturePool::GetTextureName();
            Pillow* pillow = pillows->values[i];
            if (name != "" && pillow) pillow->InitFromName(name);
        }
    }
}