#include "constellation.hpp"
#include "FileUtils.hpp"
#include "static-defines.hpp"

extern Logger& getLogger();

namespace MenuPillow
{
    Constellation Constellation::ConstellationFromFilePath(std::string filePath)
    {
        getLogger().info("found constellation @ %s:", filePath.c_str());
        std::string json = readfile(filePath);
        getLogger().info("%s", json.c_str());
        rapidjson::Document d;
        d.Parse(json.c_str());

        return Constellation(d);
    }

    std::vector<Constellation> Constellation::ConstellationsFromFolderPath(std::string folderPath)
    {
        getLogger().info("Getting constellations from %s", folderPath.c_str());
        std::vector<std::string> fileNames = {};
        std::vector<Constellation> constellations = {};
        
        if (!FileUtils::getFileNamesInDir("json", folderPath.c_str(), fileNames)) 
        {
            getLogger().error("Found 0 constellations");
            return constellations;
        }

        for (auto& name : fileNames)
        {
            Constellation temp = ConstellationFromFilePath(string_format("%s%s", folderPath.c_str(), name.c_str()));
            constellations.push_back(temp);
        }
        return constellations;
    }
}