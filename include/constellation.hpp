#pragma once
#include "CustomTypes/Pile.hpp"
#include "UnityEngine/Vector3.hpp"
#include <map>
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"

struct pillowparams {
    int type;
    UnityEngine::Vector3 position;
    UnityEngine::Vector3 rotation;
};

namespace MenuPillow
{
    class Constellation
    {
        public:
            Constellation()
            {
                this->name = "empty";
                this->pillowParams = {};
            }

            Constellation(std::string name, std::vector<pillowparams> list)
            {
                this->name = name;
                this->pillowParams = list;
            }

            Constellation(const rapidjson::Document& val)
            {
                name = val["constellationName"].GetString();
                const rapidjson::Value& params = val["piles"];
                assert(params.IsArray());
                for (auto& param : params.GetArray())
                {
                    int type = param["type"].GetInt();
                    const rapidjson::Value& pos = param["pos"];
                    const rapidjson::Value& rot = param["rot"];
                    //                                            small Y offset as to make it not inside the floor VVVVVVV
                    UnityEngine::Vector3 position = UnityEngine::Vector3(pos["x"].GetDouble(), pos["y"].GetDouble() + 0.1f, pos["z"].GetDouble());
                    UnityEngine::Vector3 rotation = UnityEngine::Vector3(rot["x"].GetDouble(), rot["y"].GetDouble(), rot["z"].GetDouble());
                    pillowparams pillowParam = {type, position, rotation};
                    pillowParams.push_back(pillowParam);
                }
            }

            static Constellation ConstellationFromFilePath(std::string filePath);
            static std::vector<Constellation> ConstellationsFromFolderPath(std::string folderPath);
            
            const std::string& get_name()
            {
                return name;
            }

            const std::vector<pillowparams>& get_params()
            {
                return pillowParams;
            }

        private:
            std::string name = "";
            std::vector<pillowparams> pillowParams = {};
    };
}