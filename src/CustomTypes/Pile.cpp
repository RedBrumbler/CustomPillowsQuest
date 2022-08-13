#include "CustomTypes/Pile.hpp"
#include "logging.hpp"

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"

DEFINE_TYPE(CustomPillows, Pile);

namespace CustomPillows {
    
    void Pile::Awake() {
        DEBUG("Awake");
        pillows = get_gameObject()->GetComponentsInChildren<Pillow*>(true);
        DEBUG("Done");
    }
    
    void Pile::Start() {
        if (!texturePool) {
            DEBUG("There is no texture pool, not auto changing the texture");
            return;
        }
        
        DEBUG("PillowCount: {}", pillows.Length());
        Pile::Shuffle();
    }

    void Pile::Shuffle() {
        for (auto pillow : pillows) {
            pillow->SetTexture(texturePool->GetTexture(""));
        }
    }

    void Pile::Hide(bool doHide) {
        get_gameObject()->SetActive(!doHide);
    }
}