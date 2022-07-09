#include "Utils/FileUtils.hpp"
#include "Constellation.hpp"
#include "logging.hpp"
#include "static-defines.hpp"

#include <fstream>
#include <fmt/core.h>

namespace CustomPillows {
    Constellation::Constellation() {}

    Constellation::Constellation(std::string_view name, std::vector<PillowParams>& list)
    {
        this->name = name;
        this->pillowParams = list;
    }

    Constellation::Constellation(const rapidjson::Document& val)
    {
        // get name from file
        name = val["constellationName"].GetString();
        
        // get all the pillow params from the file
        const rapidjson::Value& params = val["piles"];
        assert(params.IsArray());
        
        pillowParams.reserve(params.Size());

        for (auto& param : params.GetArray())
        {
            int type = param["type"].GetInt();
            const rapidjson::Value& pos = param["pos"];
            const rapidjson::Value& rot = param["rot"];
            //                                            small Y offset as to make it not inside the floor VVVVVVV
            UnityEngine::Vector3 position = UnityEngine::Vector3(pos["x"].GetDouble(), pos["y"].GetDouble() + 0.1f, pos["z"].GetDouble());
            UnityEngine::Vector3 rotation = UnityEngine::Vector3(rot["x"].GetDouble(), rot["y"].GetDouble(), rot["z"].GetDouble());
            
            // add to this constellations list of piles
            pillowParams.emplace_back(type, position, rotation);
        }
    }

    Constellation Constellation::ConstellationFromFilePath(std::string_view filePath) {
        // load the file
        INFO("Loading constellation from file {}", filePath);
        auto contents = readfile(filePath);
        rapidjson::Document doc;
        doc.Parse(contents.c_str());
        assert(doc.IsObject());
        
        // create the constellation
        return Constellation(doc);
    }

    std::vector<Constellation> Constellation::ConstellationsFromFolderPath(std::string_view folderPath) {
        // get all the files in the folder
        std::vector<std::string> fileNames;
        FileUtils::GetFilesInFolderPath("json", folderPath, fileNames);
        
        // create a vector of constellations
        std::vector<Constellation> constellations;
        constellations.reserve(fileNames.size());
        
        // load all the constellations
        for (auto& file : fileNames) {
            constellations.emplace_back(ConstellationFromFilePath(fmt::format("{}{}", folderPath, file)));
        }
        
        return constellations;
    }
}