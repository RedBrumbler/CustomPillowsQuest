#pragma once
#include "UnityEngine/Texture2D.hpp"
#include <vector>
#include <map>
namespace MenuPillow
{
    class TexturePool
    {
        public:
            UnityEngine::Texture2D* GetTexture(int index = -1);
            void ReloadTextures();

            void AddTexture(std::string name);
            void RemoveTexture(std::string name);
        private:
            void LoadAllTextures();

            std::map<std::string, UnityEngine::Texture2D*> textures;
            std::map<std::string, UnityEngine::Texture2D*> activeTextures;
    };
}