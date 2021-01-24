#include "Pile.hpp"
#include "UnityEngine/WaitUntil.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Coroutine.hpp"
#include "System/Collections/IEnumerator.hpp"
#include "System/Func_1.hpp"
#include "UnityEngine/GameObject.hpp"

DEFINE_CLASS(MenuPillow::Pile);

namespace MenuPillow
{
    Array<Pillow*>* Pile::GetPillows()
    {
        return get_gameObject()->GetComponentsInChildren<Pillow*>(true);
    }

    void Pile::Awake()
    {
        childCount = get_transform()->get_childCount();
        auto coroutine = UnityEngine::WaitUntil::New_ctor(il2cpp_utils::MakeDelegate<System::Func_1<bool>*>(classof(System::Func_1<bool>*), this,
        +[](Pile* self){
            if (self->childIndex >= self->childCount)
            {
                return true;
            }
            UnityEngine::GameObject* child = self->get_transform()->GetChild(self->childIndex)->get_gameObject()
            if (!child->GetComponent<Pillow*>()) child->AddComponent<Pillow*>();
            self->childIndex++;
            return false;
        }));

        StartCoroutine(reinterpret_cast<System::Collections::IEnumerator*>(coroutine));
    }
}