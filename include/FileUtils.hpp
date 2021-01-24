#pragma once
#include <string>
#include <vector>
#include "UnityEngine/Texture2D.hpp"

class FileUtils
{
    public:
        static bool getFileNamesInDir(std::string extension, std::string dir, std::vector<std::string>& fileNames);
        static std::string getFileExtension(const std::string& FileName);
        static std::string getFileName(std::string filePath);
        static std::string getFolderName(std::string filePath);

        static UnityEngine::Texture2D* TextureFromFile(std::string filePath, int width, int height);
};