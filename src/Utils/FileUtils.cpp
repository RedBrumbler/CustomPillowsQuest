#include "Utils/FileUtils.hpp"

#include <fstream>
#include <dirent.h>
#include "logging.hpp"

#include "UnityEngine/TextureFormat.hpp"
#include "UnityEngine/TextureWrapMode.hpp"
#include "UnityEngine/ImageConversion.hpp"

namespace FileUtils {
    std::string_view GetFileName(std::string_view path, bool removeExtension)
    {
        int pos = path.find_last_of("/");
        if (pos != std::string::npos)
            return removeExtension ? RemoveExtension(path.substr(pos + 1)) : path.substr(pos + 1);
        else
            return removeExtension ? RemoveExtension(path) : path;
    }

    std::string_view RemoveExtension(std::string_view path)
    {
        int pos = path.find_last_of(".");
        if (pos != std::string::npos)
            return path.substr(0, pos);
        return path;
    }

    std::string_view GetExtension(std::string_view path)
    {
        int pos = path.find_last_of(".");
        if (pos != std::string::npos)
            return path.substr(pos + 1);
        return "";
    }
    
    bool GetFilesInFolderPath(std::string_view extension, std::string_view filePath, std::vector<std::string>& out)
    {
        bool foundTheExtension = false;
        struct DIR* fileDir = opendir(filePath.data());
        struct dirent* files;
        if (fileDir != NULL)
        {
            while ((files = readdir(fileDir)) != NULL)
            {
                char* fileName = files->d_name;
                INFO("Found file {}", fileName);
                if (!strcmp(fileName, ".") || !strcmp(fileName, ".."))
                    continue;
                if (extension == "" || GetExtension(fileName) == extension)
                {
                    out.push_back(fileName);
                    foundTheExtension = true;
                }
            }
            closedir(fileDir);
        }
        return foundTheExtension;
    }

    UnityEngine::Texture2D* FileToTexture(std::string_view path) {
        DEBUG("Loading texture @ {}", path);
        std::ifstream instream(path, std::ios::in | std::ios::binary | std::ios::ate);
        unsigned long size = instream.tellg();
        instream.seekg(0, instream.beg);

        // this way we skip the copy step from vector to array, and just read directly into the array, making it quicker
        ArrayW<uint8_t> bytes = ArrayW<uint8_t>(static_cast<il2cpp_array_size_t>(size));
        instream.read(reinterpret_cast<char*>(&bytes[0]), size);
        
        UnityEngine::Texture2D* texture = UnityEngine::Texture2D::New_ctor(0, 0, UnityEngine::TextureFormat::RGBA32, false, false);
        UnityEngine::ImageConversion::LoadImage(texture, bytes, false);
        texture->set_wrapMode(UnityEngine::TextureWrapMode::Clamp);

        return texture;
    }

}