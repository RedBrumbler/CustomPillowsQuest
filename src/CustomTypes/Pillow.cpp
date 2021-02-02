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
int id = 0;
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
        Texture2D* tex = FileUtils::FileToTexture(imagePath);
        // get renderer & mat
        SkinnedMeshRenderer* renderer = GetComponent<SkinnedMeshRenderer*>();
        Material* mat = renderer->get_material();
        if (!mainTex) mainTex = il2cpp_utils::createcsstr("_mainTex", il2cpp_utils::StringType::Manual);
        if (!id) id = Shader::PropertyToID(mainTex);
        // set main tex
        Object::Destroy(mat->GetTexture(id));
        mat->SetTexture(mainTex, tex);
    }
}