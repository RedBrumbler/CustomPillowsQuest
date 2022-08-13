#pragma once
#include "UnityEngine/Vector3.hpp"
#include <map>
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"

namespace CustomPillows
{
    class Constellation
    {
        public:
            struct PillowParams {
                int type;
                UnityEngine::Vector3 position;
                UnityEngine::Vector3 rotation;

                PillowParams(int type, UnityEngine::Vector3 position, UnityEngine::Vector3 rotation) : type(type), position(position), rotation(rotation) {}
            };

            Constellation();
            Constellation(std::string_view name, std::vector<PillowParams>& list);
            Constellation(const rapidjson::Document& val);

            /// @brief load the constellation from a json file
            static Constellation ConstellationFromFilePath(std::string_view filePath);
            /// @brief load all constellations in this folder
            static std::vector<Constellation> ConstellationsFromFolderPath(std::string_view folderPath);
            
            /// @brief gets the name
            std::string_view get_name() const { return name; }

            /// @brief gets all the params
            const std::vector<PillowParams>& get_params() const { return pillowParams; }

        private:
            std::string name = "empty";
            std::vector<PillowParams> pillowParams = {};
    };
}