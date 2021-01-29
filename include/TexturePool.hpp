#pragma once
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/Sprite.hpp"
#include <vector>

namespace MenuPillow
{
    class TexturePool
    {
        public:
            static std::string GetTextureName(int index = -1);
            static void ReloadTextures();
            static void LoadAllTextures();
            static bool GetIsActive(std::string name);
            static void AddTexture(std::string name);
            static void RemoveTexture(std::string name);
            static const std::vector<std::string>& GetTextureVector()
            {
                return textures;
            }

        private:
            static inline std::vector<std::string> textures = {};
            static inline std::vector<std::string> activeTextures = {};
    };
}