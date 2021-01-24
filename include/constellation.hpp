#pragma once
#include "Pile.hpp"
#include "UnityEngine/Vector3.hpp"
#include <map>
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"

struct pillowparams {
    int type;
    UnityEngine::Vector3 position;
    UnityEngine::Vector3 rotation;

    //pillowparams(int t, )
};

namespace MenuPillow
{
    class Constellation
    {
        public:
            Constellation(std::string name, std::vector<pillowparams> list)
            {
                this->name = name;
                this->params = list;
            }

            Constellation(const rapidjson::Value& val)
            {
                name = val["name"].GetString();

                const rapidjson::Value& positions = val["positions"];
                assert(positions.IsArray());
                for (auto& pos : positions.GetArray())
                {
                    int type = pos["type"].GetInt();
                    UnityEngine::Vector3 position = UnityEngine::Vector3(pos["pos"]["x"].GetDouble(), pos["pos"]["y"].GetDouble(), pos["pos"]["z"].GetDouble());
                    UnityEngine::Vector3 rotation = UnityEngine::Vector3(pos["pos"]["x"].GetDouble(), pos["pos"]["y"].GetDouble(), pos["pos"]["z"].GetDouble());
                    pillowparams param = {type, position, rotation};
                    params.push_back(param);
                }
            }

            const std::string& get_name()
            {
                return name;
            }

            const std::vector<pillowparams>& get_params()
            {
                return params;
            }

        private:
            std::string name = "";
            std::vector<pillowparams> params = {};
    };
}