#include "FileUtils.hpp"
#include <fstream>
#include <dirent.h>
#include "UnityEngine/ImageConversion.hpp"
#include "UnityEngine/TextureFormat.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils-methods.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

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
            if(foundExtension == extension)
            {
                fileNames.push_back(std::string(files->d_name));
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

UnityEngine::Texture2D* FileUtils::TextureFromFile(std::string filePath, int width, int height)
{
    std::ifstream instream(filePath, std::ios::in | std::ios::binary);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(instream)), std::istreambuf_iterator<char>());
    Array<uint8_t>* bytes = il2cpp_utils::vectorToArray(data);
    UnityEngine::Texture2D* texture = UnityEngine::Texture2D::New_ctor(width, height, UnityEngine::TextureFormat::RGBA32, false, false);
    UnityEngine::ImageConversion::LoadImage(texture, bytes, false);
    return texture;
}
