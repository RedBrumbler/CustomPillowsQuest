#include "FileUtils.hpp"
#include <fstream>
#include <dirent.h>
#include "UnityEngine/ImageConversion.hpp"
#include "UnityEngine/TextureFormat.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/Vector4.hpp"
#include "UnityEngine/SpriteMeshType.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils-methods.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "UnityEngine/Texture2D.hpp"

extern Logger& getLogger();

bool FileUtils::getFileNamesInDir(std::string extension, std::string dir, std::vector<std::string>& fileNames)
{
    bool foundTheExtension = false; 
    DIR* fileDir = opendir(dir.data());
    struct dirent *files;
    if(fileDir != NULL)
    {
        while((files = readdir(fileDir)) != NULL)
        {
            std::string foundExtension = getFileExtension(files->d_name);
            std::string name = files->d_name;
            if(foundExtension.find(extension) != std::string::npos && name != "." && name != "..")
            {
                fileNames.push_back(std::string(name));
                foundTheExtension = true; 
            }
        }
        closedir(fileDir);
        if(!foundTheExtension) return false; 
        return true;
    } else return false;
}

std::string FileUtils::getFileExtension(const std::string& filename)
{
    if(filename.find_last_of(".") != std::string::npos)
        return filename.substr(filename.find_last_of(".")+1);
    return "";
}

std::string FileUtils::getFileName(std::string filepath)
{
    if(filepath.find_last_of("/") != std::string::npos)
        return filepath.substr(filepath.find_last_of("/")+1);
    return "";
}

std::string FileUtils::getFolderName(std::string filepath)
{
    if(filepath.find_last_of("/") != std::string::npos)
        return filepath.substr(0, filepath.find_last_of("/"));
    return "";
}

UnityEngine::Texture2D* FileUtils::FileToTexture(std::string filePath)
{
    std::ifstream instream(filePath, std::ios::in | std::ios::binary);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());
    Array<uint8_t>* bytes = il2cpp_utils::vectorToArray(data);
    UnityEngine::Texture2D* texture = UnityEngine::Texture2D::New_ctor(0, 0, UnityEngine::TextureFormat::RGBA32, false, false);
    UnityEngine::ImageConversion::LoadImage(texture, bytes, false);
    return texture;
}

UnityEngine::Sprite* FileUtils::FileToSprite(std::string filePath)
{
    UnityEngine::Texture2D* texture = FileToTexture(filePath);
    return UnityEngine::Sprite::Create(texture, UnityEngine::Rect(0.0f, 0.0f, (float)texture->get_width(), (float)texture->get_height()), UnityEngine::Vector2(0.5f,0.5f), 1024.0f, 1u, UnityEngine::SpriteMeshType::FullRect, UnityEngine::Vector4(0.0f, 0.0f, 0.0f, 0.0f), false);
}

std::string FileUtils::RemoveExtension(std::string fileName)
{
    fileName.erase(fileName.find_last_of("."));

    return fileName;
}
