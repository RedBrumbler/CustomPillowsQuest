#include "config.hpp"
#include "logging.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"

#include "beatsaber-hook/shared/rapidjson/include/rapidjson/document.h"

extern ModInfo modInfo;
Config config;

Configuration& getConfig()
{
    static Configuration config(modInfo);
    config.Load();
    return config;
}

rapidjson::Value GetTexturesArray(rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value array(rapidjson::kArrayType);
    for (auto& tex : config.lastActiveTextures)
    {
        rapidjson::Value texVal(tex.c_str(), tex.size(), allocator);
        array.PushBack(texVal, allocator);
    }

    return array;
}

void SaveConfig()
{
    INFO("Saving Configuration...");
    rapidjson::Document& doc = getConfig().config;
    doc.RemoveAllMembers();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    doc.AddMember("enabled", config.enabled, allocator);
    doc.AddMember("keepInLevel", config.keepInLevel, allocator);
    doc.AddMember("keepInMulti", config.keepInMulti, allocator);
    doc.AddMember("lastActiveConstellation", config.lastActiveConstellation, allocator);

    std::string texString = "lastActiveTextures";
    rapidjson::Value texName(texString.c_str(), texString.size(), allocator);
    doc.AddMember(texName, GetTexturesArray(allocator), allocator);

    getConfig().Write();
    INFO("Saved Configuration!");
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

#define GETBOOL(name)                               \
    auto itr_##name = doc.FindMember(#name);        \
    if (itr_##name != doc.MemberEnd())                \
        config.name = itr_##name->value.GetBool();  \
    else                                            \
        foundEverything = false

#define GETSTRING(name)                             \
    auto itr_##name = doc.FindMember(#name);        \
    if (itr_##name != doc.MemberEnd())              \
        config.name = itr_##name->value.GetString();\
    else                                            \
        foundEverything = false

bool LoadConfig()
{
    INFO("Loading Configuration...");
    bool foundEverything = true;
    rapidjson::Document& doc = getConfig().config;

    GETBOOL(enabled);
    GETBOOL(keepInLevel);
    GETBOOL(keepInMulti);
    GETSTRING(lastActiveConstellation);

    if (doc.HasMember("lastActiveTextures") && doc["lastActiveTextures"].IsArray())
    {
        config.lastActiveTextures = LoadActiveTextureNames(doc["lastActiveTextures"]);
    }
    else
    {
        foundEverything = false;
    }
    if (foundEverything) INFO("Loaded Configuration!");
    return foundEverything;
}