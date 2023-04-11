#include "CustomTypes/Pile.hpp"
#include "logging.hpp"

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/GameObject.hpp"

DEFINE_TYPE(CustomPillows, Pile);

namespace CustomPillows {
    void Pile::Inject(TexturePool* texturePool) {
        _texturePool = texturePool;
    }

    void Pile::Start() {
        if (!_texturePool) {
            DEBUG("There is no texture pool, not auto changing the texture");
            return;
        }

        DEBUG("PillowCount: {}", pillows.Length());
        Shuffle();
    }

    void Pile::Shuffle() {
        for (auto pillow : pillows) {
            pillow->SetTexture(_texturePool->GetTexture(""));
        }
    }

    void Pile::Hide(bool doHide) {
        get_gameObject()->SetActive(!doHide);
    }
}