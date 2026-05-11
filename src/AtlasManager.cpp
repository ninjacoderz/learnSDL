#include "AtlasManager.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <fstream>
#include <sstream>

// Dùng nlohmann/json hoặc parse thủ công
// Ở đây dùng simple manual parse để không phụ thuộc thư viện ngoài
// (tương đương cJSON trong code C cũ)

AtlasManager& AtlasManager::Get() {
    static AtlasManager instance;
    return instance;
}

// Helper: đọc toàn bộ file thành string
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

// Helper: lấy value string từ "key" : "value"
static std::string extractString(const std::string& block, const std::string& key) {
    std::string search = "\"" + key + "\"";
    size_t pos = block.find(search);
    if (pos == std::string::npos) return "";
    pos = block.find(":", pos);
    if (pos == std::string::npos) return "";
    pos = block.find("\"", pos);
    if (pos == std::string::npos) return "";
    size_t end = block.find("\"", pos + 1);
    return block.substr(pos + 1, end - pos - 1);
}

// Helper: lấy value number từ "key" : 123
static float extractNumber(const std::string& block, const std::string& key) {
    std::string search = "\"" + key + "\"";
    size_t pos = block.find(search);
    if (pos == std::string::npos) return 0.f;
    pos = block.find(":", pos);
    if (pos == std::string::npos) return 0.f;
    // skip whitespace
    pos++;
    while (pos < block.size() && (block[pos] == ' ' || block[pos] == '\t')) pos++;
    return std::stof(block.substr(pos));
}

bool AtlasManager::Load(SDL_Renderer* renderer,
                        const std::string& pngPath,
                        const std::string& jsonPath) {
    // 1. Load texture atlas
    mAtlasTex = IMG_LoadTexture(renderer, pngPath.c_str());
    SDL_Log("Atlas texture: %s → %s", 
            pngPath.c_str(),
            mAtlasTex ? "OK" : "FAILED");
    if (!mAtlasTex) {
        SDL_Log("AtlasManager: failed to load '%s': %s", pngPath.c_str(), SDL_GetError());
        return false;
    }
    SDL_Log("AtlasManager: loaded atlas texture '%s'", pngPath.c_str());

    // 2. Parse JSON
    std::string json = readFileToString(jsonPath);

    if (json.empty()) return false;

    // Parse từng object { ... } trong array
    size_t pos = 0;
    while (true) {
        size_t start = json.find('{', pos);
        if (start == std::string::npos) break;

        size_t end = json.find('}', start);
        if (end == std::string::npos) break;

        std::string block = json.substr(start, end - start + 1);

        std::string filename = extractString(block, "filename");
        if (!filename.empty()) {
            AtlasEntry entry;
            entry.srcRect.x       = extractNumber(block, "x");
            entry.srcRect.y       = extractNumber(block, "y");
            entry.srcRect.w       = extractNumber(block, "w");
            entry.srcRect.h       = extractNumber(block, "h");
            entry.rotated         = (extractNumber(block, "rotated") != 0.f);
            mEntries[filename]    = entry;
        }

        pos = end + 1;
    }

    SDL_Log("AtlasManager: loaded %zu entries from '%s'",
            mEntries.size(), jsonPath.c_str());
            
    return true;
}

const AtlasEntry* AtlasManager::GetEntry(const std::string& filename) const {
    auto it = mEntries.find(filename);
    if (it == mEntries.end()) {
        // SDL_Log("AtlasManager: no entry for '%s'", filename.c_str());
        return nullptr;
    }
    return &it->second;
}