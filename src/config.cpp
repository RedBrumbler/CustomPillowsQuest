#include "config.hpp"
#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"
#include "modloader/shared/modloader.hpp"

config_t config;

extern ModInfo modInfo;
extern Logger& getLogger();

Configuration& getConfig()
{
    static Configuration config(modInfo);
    config.Load();
    return config;
}

rapidjson::Value GetTexturesArray(rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value array(rapidjson::kArrayType);
    for (auto tex : config.lastActiveTextures)
    {
        rapidjson::Value texVal(tex.c_str(), tex.size(), allocator);
        array.PushBack(texVal, allocator);
    }

    return array;
}

void SaveConfig()
{
    getLogger().WithContext("Save Config").info("Saving Configuration...");
    rapidjson::Document& doc = getConfig().config;
    doc.RemoveAllMembers();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    doc.AddMember("enabled", config.enabled, allocator);
    doc.AddMember("lastActiveConstellation", config.lastActiveConstellation, allocator);

    std::string texString = "lastActiveTextures";
    rapidjson::Value texName(texString.c_str(), texString.size(), allocator);
    doc.AddMember(texName, GetTexturesArray(allocator), allocator);

    getConfig().Write();
    getLogger().WithContext("Save Config").info("Saved Configuration!");
}


std::vector<std::string> LoadActiveTextureNames(rapidjson::Value& texArray)
{
    std::vector<std::string> result = {};
    assert(texArray.IsArray());
    for (auto& val : texArray.GetArray())
    {
        result.push_back(val.GetString());
    }

    return result;
}

bool LoadConfig()
{
    getLogger().WithContext("Load Config").info("Loading Configuration...");
    bool foundEverything = true;
    rapidjson::Document& doc = getConfig().config;

    if (doc.HasMember("enabled") && doc["enabled"].IsBool())
    {
        config.enabled = doc["enabled"].GetBool();
    }
    else
    {
        foundEverything = false;
    }
    if (doc.HasMember("lastActiveConstellation") && doc["lastActiveConstellation"].IsString())
    {
        config.lastActiveConstellation = doc["lastActiveConstellation"].GetString();
    }
    else
    {
        foundEverything = false;
    }
    if (doc.HasMember("lastActiveTextures") && doc["lastActiveTextures"].IsArray())
    {
        config.lastActiveTextures = LoadActiveTextureNames(doc["lastActiveTextures"]);
    }
    else
    {
        foundEverything = false;
    }
    if (foundEverything) getLogger().WithContext("Load Config").info("Loaded Configuration!");
    return foundEverything;
}