#include "CustomTypes/Pillow.hpp"
#include "UnityEngine/SkinnedMeshRenderer.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Shader.hpp"
#include "UnityEngine/Texture.hpp"
#include "UnityEngine/Sprite.hpp"
#include "static-defines.hpp"

#include "questui/shared/BeatSaberUI.hpp"

DEFINE_CLASS(MenuPillow::Pillow);

using namespace UnityEngine;

static Il2CppString* mainTex = nullptr;
extern Logger& getLogger();

namespace MenuPillow
{
    void Pillow::Init(UnityEngine::Texture2D* texture)
    {
        SkinnedMeshRenderer* renderer = GetComponent<SkinnedMeshRenderer*>();
        Material* mat = renderer->get_material();
        if (!mainTex) mainTex = il2cpp_utils::createcsstr("_mainTex", il2cpp_utils::StringType::Manual);
        mat->SetTexture(mainTex, reinterpret_cast<Texture*>(texture));
    }

    void Pillow::InitFromName(std::string texName)
    {
        std::string imagePath = IMAGEPATH + texName;
        Sprite* sprite = QuestUI::BeatSaberUI::FileToSprite(imagePath, 474, 1012);
        SkinnedMeshRenderer* renderer = GetComponent<SkinnedMeshRenderer*>();
        Material* mat = renderer->get_material();
        if (!mainTex) mainTex = il2cpp_utils::createcsstr("_mainTex", il2cpp_utils::StringType::Manual);
        mat->SetTexture(mainTex, sprite->get_texture());
        Object::Destroy(sprite);
    }
}