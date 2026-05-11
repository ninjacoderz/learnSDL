#include "ISORenderer.h"

ISORenderer& ISORenderer::Get() {
    static ISORenderer instance;
    return instance;
}

void ISORenderer::toISO(int x, int z, float& sx, float& sy) const {
    // Port trực tiếp từ iso.c toISO()
    sx = static_cast<float>(originX + (x * tileW / 2) + (z * tileW / 2));
    sy = static_cast<float>(originY + (z * tileH / 2) - (x * tileH / 2));
}

// ── Static buffer (map tiles) ──────────────────────────────

void ISORenderer::SubmitStatic(int x, int z, SDL_Texture* tex,
                                SDL_FRect src, float offSX, float offSY) {
    ISOObject obj;
    toISO(x, z, obj.sx, obj.sy);
    obj.sx += offSX;  obj.sy += offSY;
    obj.x = x;        obj.z = z;
    obj.tex = tex;    obj.srcRect = src;
    mStaticBuffer.push_back(obj);
    mStaticSorted = false;
}

void ISORenderer::BuildStaticCache() {
    SDL_Log("BuildStaticCache: %zu objects", mStaticBuffer.size());
    // Sort 1 lần — không cần sort lại trừ khi map thay đổi
    int badCount = 0;
    for (auto& obj : mStaticBuffer) {
        if (!obj.tex || obj.srcRect.w <= 0 || obj.srcRect.h <= 0) {
            SDL_Log("BAD object: tex=%p w=%.0f h=%.0f",
                    obj.tex, obj.srcRect.w, obj.srcRect.h);
            badCount++;
        }
    }
    SDL_Log("BuildStaticCache: %zu total, %d bad entries",
            mStaticBuffer.size(), badCount);
    std::sort(mStaticBuffer.begin(), mStaticBuffer.end(),
              [](const ISOObject& a, const ISOObject& b) {
                  return a.sy < b.sy;
              });
    mStaticSorted = true;
    SDL_Log("ISORenderer: static cache built (%zu tiles)", mStaticBuffer.size());
}

// ── Dynamic buffer (player, enemy) ────────────────────────

void ISORenderer::Submit(int x, int z, SDL_Texture* tex,
                         SDL_FRect src, float offSX, float offSY,
                         double angle, SDL_FlipMode flip) {
    ISOObject obj;
    toISO(x, z, obj.sx, obj.sy);
    obj.sx += offSX;  obj.sy += offSY;
    obj.x = x;        obj.z = z;
    obj.tex = tex;    obj.srcRect = src;
    obj.angle = angle; obj.flip = flip;
    mDynamicBuffer.push_back(obj);
}

void ISORenderer::ClearDynamic() {
    mDynamicBuffer.clear();
}

// ── Flush: merge static + dynamic → render ────────────────

void ISORenderer::Flush(SDL_Renderer* renderer) {
    if (!mStaticBuffer.empty()) {
        auto& o = mStaticBuffer[0];
        SDL_Log("First tile: sx=%.0f sy=%.0f w=%.0f h=%.0f",
                o.sx, o.sy, o.srcRect.w, o.srcRect.h);
    }
    if (!mStaticSorted) BuildStaticCache();

    // Sort dynamic (ít objects hơn nhiều)
    std::sort(mDynamicBuffer.begin(), mDynamicBuffer.end(),
              [](const ISOObject& a, const ISOObject& b) {
                  return a.sy < b.sy;
              });

    // Merge 2 sorted lists → painter's algorithm đúng
    auto sit = mStaticBuffer.begin();
    auto dit = mDynamicBuffer.begin();

    auto renderObj = [&](const ISOObject& obj) {
        SDL_FRect dst { obj.sx, obj.sy, obj.srcRect.w, obj.srcRect.h };
        SDL_RenderTextureRotated(renderer,
            obj.tex, &obj.srcRect, &dst,
            obj.angle, nullptr, obj.flip);
    };

    while (sit != mStaticBuffer.end() || dit != mDynamicBuffer.end()) {
        bool useStatic = (dit == mDynamicBuffer.end()) ||
                         (sit != mStaticBuffer.end() &&
                          sit->sy <= dit->sy);
        if (useStatic) renderObj(*sit++);
        else           renderObj(*dit++);
    }
}