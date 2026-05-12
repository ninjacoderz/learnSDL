#include "AtlasManager.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <fstream>
#include <sstream>

// RapidJSON — header-only, không cần link thêm gì
#include "include/rapidjson/document.h"
#include "include/rapidjson/error/en.h"

AtlasManager& AtlasManager::Get() {
    static AtlasManager instance;
    return instance;
}

static std::string readFileToString(const std::string& path) {
    std::ifstream f(path);
    if (!f.is_open()) {
        SDL_Log("AtlasManager: cannot open '%s'", path.c_str());
        return "";
    }
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

bool AtlasManager::Load(SDL_Renderer* renderer,
                        const std::string& pngPath,
                        const std::string& jsonPath) {
    // 1. Load atlas texture
    mAtlasTex = IMG_LoadTexture(renderer, pngPath.c_str());
    if (!mAtlasTex) {
        SDL_Log("AtlasManager: failed to load texture '%s': %s",
                pngPath.c_str(), SDL_GetError());
        return false;
    }
    SDL_Log("Atlas texture: %s -> OK", pngPath.c_str());

    // 2. Doc JSON file
    std::string json = readFileToString(jsonPath);
    if (json.empty()) return false;

    // 3. Parse bang RapidJSON
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    if (doc.HasParseError()) {
        SDL_Log("AtlasManager: JSON parse error (offset %zu): %s",
                doc.GetErrorOffset(),
                rapidjson::GetParseError_En(doc.GetParseError()));
        return false;
    }

    if (!doc.IsArray()) {
        SDL_Log("AtlasManager: JSON root is not an array");
        return false;
    }

    // 4. Duyet tung entry trong array
    for (const auto& node : doc.GetArray()) {
        if (!node.IsObject())            continue;
        if (!node.HasMember("filename")) continue;
        if (!node.HasMember("x"))        continue;

        AtlasEntry entry;
        entry.srcRect.x = static_cast<float>(node["x"].GetInt());
        entry.srcRect.y = static_cast<float>(node["y"].GetInt());
        entry.srcRect.w = static_cast<float>(node["w"].GetInt());
        entry.srcRect.h = static_cast<float>(node["h"].GetInt());
        entry.rotated   = node.HasMember("rotated") && node["rotated"].GetInt() != 0;

        mEntries[node["filename"].GetString()] = entry;
    }

    SDL_Log("AtlasManager: loaded %zu entries from '%s'",
            mEntries.size(), jsonPath.c_str());
    return true;
}

const AtlasEntry* AtlasManager::GetEntry(const std::string& filename,
                                          bool required) const {
    auto it = mEntries.find(filename);
    if (it == mEntries.end()) {
        if (required) {
            SDL_Log("AtlasManager: MISSING required entry '%s'", filename.c_str());
        }
        return nullptr;
    }
    return &it->second;
}

void AtlasManager::Shutdown() {
    if (mAtlasTex) {
        SDL_DestroyTexture(mAtlasTex);
        mAtlasTex = nullptr;
    }
    mEntries.clear();
    SDL_Log("AtlasManager: shutdown");
}