#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <algorithm>

struct ISOObject {
    float sx, sy;        // screen pixel (sau toISO)
    int   x,  z;         // grid position gốc
    SDL_Texture* tex;
    SDL_FRect    srcRect;
    double       angle = 0.0;
    SDL_FlipMode flip  = SDL_FLIP_NONE;
};

class ISORenderer {
public:
    static ISORenderer& Get();

    // Static buffer: map tiles — submit 1 lần, giữ đến khi map thay đổi
    void SubmitStatic(int x, int z, SDL_Texture* tex, SDL_FRect src,
                      float offSX = 0.f, float offSY = 0.f);
    void BuildStaticCache(); // sort static buffer 1 lần

    // Dynamic buffer: player, enemy — clear + submit mỗi frame
    void Submit(int x, int z, SDL_Texture* tex, SDL_FRect src,
                float offSX = 0.f, float offSY = 0.f,
                double angle = 0.0, SDL_FlipMode flip = SDL_FLIP_NONE);

    void ClearDynamic();  // gọi đầu mỗi frame
    void Flush(SDL_Renderer* renderer); // merge static+dynamic → render

    // ISO config
    int tileW   = 64;
    int tileH   = 32;
    int originX = 400;
    int originY = 100;

private:
    ISORenderer() = default;
    void toISO(int x, int z, float& sx, float& sy) const;

    std::vector<ISOObject> mStaticBuffer;   // sorted 1 lần khi map load
    std::vector<ISOObject> mDynamicBuffer;  // sort mỗi frame
    bool mStaticSorted = false;
};