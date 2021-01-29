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
        get_transform()->set_localScale(UnityEngine::Vector3::get_one() * 0.4f);
        auto coroutine = WaitUntil::New_ctor(il2cpp_utils::MakeDelegate<System::Func_1<bool>*>(classof(System::Func_1<bool>*), this,
        +[](Pile* self){
            if (self->childIndex >= self->childCount)
            {
                self->randomizeTextures = true;
                return true;
            }
            Transform* child = self->get_transform()->GetChild(self->childIndex);
            Transform* mesh = child->Find(meshName);
            if (!mesh->get_gameObject()->GetComponent<Pillow*>()) mesh->get_gameObject()->AddComponent<Pillow*>();
            self->childIndex++;
            return false;
        }));

        StartCoroutine(reinterpret_cast<System::Collections::IEnumerator*>(coroutine));
    }

    void Pile::Update()
    {
        if (randomizeTextures)
        {
            randomizeTextures = false;
            RandomizeTextures();
        }
    }

    /*
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
    */
    
    struct PillowData {
        int index;
        int count;
        Array<Pillow*>* pillows;
    };

    void Pile::RandomizeTextures()
    {
        Array<Pillow*>* pillows = GetPillows();
        QuestUI::CustomDataType* wrapper = CRASH_UNLESS(il2cpp_utils::New<QuestUI::CustomDataType*, il2cpp_utils::CreationType::Manual>(classof(QuestUI::CustomDataType*)));
        PillowData* data = new PillowData();
        wrapper->data = data;
        data->index = 0;
        data->count = pillows->Length();
        data->pillows = pillows;
        auto coroutine = UnityEngine::WaitUntil::New_ctor(il2cpp_utils::MakeDelegate<System::Func_1<bool>*>(classof(System::Func_1<bool>*), wrapper,
            +[](QuestUI::CustomDataType* wrapper){
                PillowData* data = (PillowData*)wrapper->data;
                if (data->index >= data->count)
                {
                    free(wrapper);
                    return true;
                }
                std::string name = TexturePool::GetTextureName();
                Pillow* pillow = data->pillows->values[data->index];
                if (name != "" && pillow) pillow->InitFromName(name);
                data->index++;
                return false;
            }));

        UnityEngine::MonoBehaviour::StartCoroutine(reinterpret_cast<System::Collections::IEnumerator*>(coroutine));
    }
    
}
