#include "TexturePool.hpp"
#include "static-defines.hpp"
#include "FileUtils.hpp"

namespace MenuPillow
{
    UnityEngine::Texture2D* TexturePool::GetTexture(int index)
    {
        if (!activeTextures.size()) return nullptr;
        if (index < 0) index = rand() % activeTextures.size();
        int counter = 0;
        for (auto& pair : activeTextures)
        {
            if (counter == index) return pair.second;
            counter++;
        }
        return nullptr;
    }

    void TexturePool::ReloadTextures()
    {
        activeTextures.clear();
        textures.clear();
        LoadAllTextures();
    }

    void TexturePool::AddTexture(std::string name)
    {
        std::map<std::string, UnityEngine::Texture2D*>::iterator it = textures.find(name);

        if (it != textures.end()) 
        {
            std::string key = it->first;
            UnityEngine::Texture2D* texture = it->second;
            activeTextures[key] = texture;
        }
    }

    void TexturePool::RemoveTexture(std::string name)
    {
        std::map<std::string, UnityEngine::Texture2D*>::iterator it = activeTextures.find(name);

        if (it != activeTextures.end()) 
        {
            activeTextures.erase(it);
        }
    }

    void TexturePool::LoadAllTextures()
    {
        std::vector<std::string> fileNames;

        FileUtils::getFileNamesInDir(".png", IMAGEPATH, fileNames);

        for (auto name : fileNames)
        {
            std::string path = IMAGEPATH + name;

            textures[name] = FileUtils::TextureFromFile(path, 474, 2012);
        }
    }
}