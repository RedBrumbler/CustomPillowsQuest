#include "CustomTypes/Pillow.hpp"
#include "UnityEngine/SkinnedMeshRenderer.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Shader.hpp"
#include "UnityEngine/Texture.hpp"
#include "UnityEngine/Sprite.hpp"
#include "static-defines.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "FileUtils.hpp"

DEFINE_CLASS(MenuPillow::Pillow);

using namespace UnityEngine;

static Il2CppString* mainTex = nullptr;
extern Logger& getLogger();

namespace MenuPillow
{
    // not really used
    void Pillow::Init(UnityEngine::Texture2D* texture)
    {
        SkinnedMeshRenderer* renderer = GetComponent<SkinnedMeshRenderer*>();
        Material* mat = renderer->get_material();
        if (!mainTex) mainTex = il2cpp_utils::createcsstr("_mainTex", il2cpp_utils::StringType::Manual);
        mat->SetTexture(mainTex, reinterpret_cast<Texture*>(texture));
    }

    // set texture by loading the sprite from file, and immediately destroy the sprite again
    void Pillow::InitFromName(std::string texName)
    {
        // get path
        std::string imagePath = IMAGEPATH + texName;
        // get sprite
        Sprite* sprite = FileUtils::FileToSprite(imagePath, 474, 1012);
        // get renderer & mat
        SkinnedMeshRenderer* renderer = GetComponent<SkinnedMeshRenderer*>();
        Material* mat = renderer->get_material();
        if (!mainTex) mainTex = il2cpp_utils::createcsstr("_mainTex", il2cpp_utils::StringType::Manual);
        // set main tex
        mat->SetTexture(mainTex, sprite->get_texture());
        // destroy sprite
        Object::Destroy(sprite);
    }
}