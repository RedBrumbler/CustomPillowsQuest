#include "CustomTypes/Pillow.hpp"
#include "logging.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Shader.hpp"
#include "UnityEngine/SkinnedMeshRenderer.hpp"

DEFINE_TYPE(CustomPillows, Pillow);

using namespace UnityEngine;

namespace CustomPillows {
    void Pillow::Awake() {
        if (pillowRenderer) material = pillowRenderer->get_material();
    }

    void Pillow::SetTexture(Texture2D* texture) {
        if (!material || !material->m_CachedPtr.m_value) {
            DEBUG("There is no material, not changing the texture");
            return;
        }
        INFO("Setting texture");

        static int mainTexId = Shader::PropertyToID("_mainTex");
        material->SetTexture(mainTexId, texture);
    }
}