#include "constellation.hpp"
#include "FileUtils.hpp"
#include "static-defines.hpp"

extern Logger& getLogger();

namespace MenuPillow
{
    Constellation Constellation::ConstellationFromFilePath(std::string filePath)
    {
        std::string json = readfile(filePath);
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
            std::string path = string_format("%s%s", folderPath.c_str(), name.c_str());
            if (!fileexists(path.c_str())) continue;
            Constellation temp = ConstellationFromFilePath(path);
            constellations.push_back(temp);
        }
        return constellations;
    }
}