#include "TexturePool.hpp"
#include "static-defines.hpp"
#include "FileUtils.hpp"
#include "config.hpp"
#include "UnityEngine/Object.hpp"

#include "questui/shared/BeatSaberUI.hpp"

extern config_t config;

extern Logger& getLogger();

namespace MenuPillow
{
    std::string TexturePool::GetTextureName(int index)
    {
        if (!activeTextures.size()) return "";
        if (index < 0 || index >= activeTextures.size()) index = rand() % activeTextures.size();
        return activeTextures[index];
    }

    void TexturePool::ReloadTextures()
    {
        getLogger().info("Reloading Textures");
        activeTextures.clear();
        textures.clear();
        LoadAllTextures();
    }

    void TexturePool::AddTexture(std::string name)
    {
        std::vector<std::string>::iterator all = std::find(textures.begin(), textures.end(), name);
        std::vector<std::string>::iterator active = std::find(activeTextures.begin(), activeTextures.end(), name);

        if (active == activeTextures.end() && all != textures.end())
        {
            activeTextures.push_back(name);
            config.lastActiveTextures = activeTextures;
        }
    }

    bool TexturePool::GetIsActive(std::string name)
    {
        if (std::find(activeTextures.begin(), activeTextures.end(), name) != activeTextures.end()) return true;
        return false; 
    }

    void TexturePool::RemoveTexture(std::string name)
    {
        std::vector<std::string> newActive = {};

        for (auto oldName : activeTextures)
        {
            if (oldName != name) newActive.push_back(oldName); 
        }

        activeTextures = newActive;
        config.lastActiveTextures = newActive;
    }

    void TexturePool::LoadAllTextures()
    {
        if (textures.size() > 0) 
        {
            getLogger().error("Tried loading textures, but they were already loaded, aborting!");
            return;
        }
        std::vector<std::string> fileNames;

        FileUtils::getFileNamesInDir("png", IMAGEPATH, fileNames);

        for (auto name : fileNames)
        {
            textures.push_back(name);
        }

        for (auto name : config.lastActiveTextures)
        {
            std::string path = IMAGEPATH + name;
            if (!fileexists(path.c_str())) continue;
            AddTexture(name);
        }
    }
}