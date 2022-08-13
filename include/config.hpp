#pragma once
#include <string>
#include <vector>

struct Config {
    std::string lastActiveConstellation = "default";
    std::vector<std::string> lastActiveTextures = {"Cubes.png"};
    bool enabled = true;
    bool keepInLevel = false;
    bool keepInMulti = true;
};

extern Config config;

void SaveConfig();
bool LoadConfig();
