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
        static ConstString meshName{"mesh"};
        auto meshRenderer = get_transform()->Find(meshName)->get_gameObject()->GetComponent<SkinnedMeshRenderer*>();
        if (meshRenderer) material = meshRenderer->get_material();
    }

    void Pillow::SetTexture(Texture2D* texture) {
        if (!material) {
            DEBUG("There is no material, not changing the texture");
            return;
        }
        INFO("Setting texture");
        
        static int mainTexId = Shader::PropertyToID("_mainTex");
        material->SetTexture(mainTexId, texture);
    }
}