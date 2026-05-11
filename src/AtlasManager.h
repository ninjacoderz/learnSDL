#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>

struct AtlasEntry {
    SDL_FRect srcRect;   // vị trí trong atlas texture
    bool      rotated = false;
};

class AtlasManager {
public:
    static AtlasManager& Get();

    // Load atlas.png + atlas.json
    bool Load(SDL_Renderer* renderer,
              const std::string& pngPath,
              const std::string& jsonPath);

    // Lookup theo filename, ví dụ "gfx/tiles/0.png"
    // Trả nullptr nếu không tìm thấy
    const AtlasEntry* GetEntry(const std::string& filename) const;

    SDL_Texture* GetTexture() const { return mAtlasTex; }

private:
    AtlasManager() = default;

    SDL_Texture* mAtlasTex = nullptr;
    std::unordered_map<std::string, AtlasEntry> mEntries;
};