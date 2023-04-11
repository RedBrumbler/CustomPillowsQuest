#include "CustomTypes/TexturePool.hpp"
#include "Utils/FileUtils.hpp"
#include "static-defines.hpp"
#include "config.hpp"
#include "logging.hpp"

#include "UnityEngine/SpriteMeshType.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector4.hpp"

#include "System/Linq/Enumerable.hpp"
#include <stdlib.h>

DEFINE_TYPE(CustomPillows, TexturePool);

using namespace UnityEngine;

namespace CustomPillows {
    void TexturePool::ctor() {
        allTextures = NameToTexture::New_ctor();
        activeTextures = NameToTexture::New_ctor();
        inActiveTextures = NameToTexture::New_ctor();

        loading = false;
        loaded = false;
    }

    Texture2D* TexturePool::GetTexture(StringW name) {
        Texture2D* result = Texture2D::get_blackTexture();
        if (!name || name == "") {
            DEBUG("Name was empty, getting a random texture");
            if (activeTexturesArray.Length() > 0) {
                // choose a random one from active
                result = activeTexturesArray[rand() % activeTexturesArray.Length()].value;
            }
        } else if (allTextures->ContainsKey(name)) {
            // give the exact one from all
            result = allTextures->get_Item(name);
        }
        return result;
    }

    Sprite* TexturePool::GetSprite(StringW name) {
        auto texture = GetTexture(name);
        return Sprite::Create(texture, Rect(0.0f, 0.0f, (float)texture->get_width(), (float)texture->get_height()), Vector2(0.5f,0.5f), 1024.0f, 1u, SpriteMeshType::FullRect, Vector4(0.0f, 0.0f, 0.0f, 0.0f), false);
    }

    void TexturePool::ActivateTexture(StringW name) {
        INFO("Activating Texture `{}`", static_cast<std::string>(name));
        auto texture = allTextures->get_Item(name);
        if (inActiveTextures->ContainsKey(name)) {
            inActiveTextures->Remove(name);
        }
        
        activeTextures->Add(name, texture);
        UpdateArrays();
    }

    void TexturePool::DeactivateTexture(StringW name) {
        INFO("Deactivating Texture `{}`", static_cast<std::string>(name));
        auto texture = allTextures->get_Item(name);
        if (activeTextures->ContainsKey(name)) {
            activeTextures->Remove(name);
        }

        inActiveTextures->Add(name, texture);
        UpdateArrays();
    }

    void TexturePool::UpdateArrays() {
        auto activeEnumerator = activeTextures->GetEnumerator();
        std::vector<TexturePool::NameToTexturePair> activePairs;
        while (activeEnumerator.MoveNext()) activePairs.push_back(activeEnumerator.get_Current()); 
        activeTexturesArray = il2cpp_utils::vectorToArray(activePairs);

        auto inActiveEnumerator = inActiveTextures->GetEnumerator();
        std::vector<TexturePool::NameToTexturePair> inActivePairs;
        while (inActiveEnumerator.MoveNext()) inActivePairs.push_back(inActiveEnumerator.get_Current()); 
        inActiveTexturesArray = il2cpp_utils::vectorToArray(inActivePairs);
    }

    custom_types::Helpers::Coroutine TexturePool::LoadTextures(std::function<void(void)> onFinished) {
        if (loading || loaded) co_return;
        loading = true;

        // do something where we load all the textures in the texture dir
        std::vector<std::string> all{};
        FileUtils::GetFilesInFolderPath("", IMAGEPATH, all);

        DEBUG("Found {} files in " IMAGEPATH, all.size());
        // yield since we just traversed the folder
        co_yield nullptr;
        
        static std::array<std::string, 3> allowedExtensions {
            "png", "jpg", "jpeg"
        };

        int count = 0;
        for (auto file : all) {
            // get the file ext
            std::string ext{FileUtils::GetExtension(file)};
            // lowercase it
            for (auto& c : ext) c = tolower(c);

            DEBUG("File {} with ext `{}`", file, ext);

            auto allowedItr = std::find(allowedExtensions.begin(), allowedExtensions.end(), ext);

            // if the extension is not allowed, skip file
            if (allowedItr == allowedExtensions.end()) continue;

            // load texture
            auto tex = FileUtils::FileToTexture(IMAGEPATH + file);
            std::string_view justFileName = FileUtils::GetFileName(file, true);

            allTextures->Add(justFileName, tex);
            auto activeItr = std::find(config.lastActiveTextures.begin(), config.lastActiveTextures.end(), justFileName);

            if (activeItr != config.lastActiveTextures.end()) {
                // if found, it's active!
                ActivateTexture(justFileName);
            } else {
                // if not, inactive!
                DeactivateTexture(justFileName);
            }

            if ((count++) % 5 == 0) {
                // yield after some textures to space things out more
                co_yield nullptr;
            }
        }

        loaded = true;

        if (onFinished) 
            onFinished();

        loading = false;
        co_return;
    }

    void TexturePool::Dispose() {
        auto enumerator = allTextures->GetEnumerator();
        while (enumerator.MoveNext()) {
            auto entry = enumerator.get_Current();
            if (entry.value && entry.value->m_CachedPtr.m_value) {
                UnityEngine::Object::DestroyImmediate(entry.value);
            }
            entry.value = nullptr;
        }
        enumerator.Dispose();
    }
}