#pragma once
#include <string>
#include <vector>
#include "beatsaber-hook/shared/config/config-utils.hpp"

struct config_t{
    std::string lastActiveConstellation = "";
    std::vector<std::string> lastActiveTextures = {"Cubes.png"};
    bool enabled;
};

Configuration& getConfig();
void SaveConfig();
bool LoadConfig();