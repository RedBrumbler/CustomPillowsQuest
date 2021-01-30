#pragma once
#include <string>
#include <vector>
#include "beatsaber-hook/shared/config/config-utils.hpp"

struct config_t{
    std::string lastActiveConstellation = "default";
    std::vector<std::string> lastActiveTextures = {"Cubes.png"};
    bool enabled = true;
};

Configuration& getConfig();
void SaveConfig();
bool LoadConfig();