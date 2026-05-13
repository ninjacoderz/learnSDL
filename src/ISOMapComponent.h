
#include <fstream>
#include <sstream>
#include <iostream>
#include "GameMath.h"
#include "SpriteComponent.h"
#include <vector>
#include "ISORenderer.h"
#include "Defs.h"

class ISOMapComponent: public SpriteComponent {
    public:
        ISOMapComponent(class Actor* owner, int drawOrder = 10);
        void Draw(SDL_Renderer* renderer) override;
        std::string TileIndexToFilename(int index);
        void SetTexture(SDL_Texture* texture) override { mTileMapTexture = texture; }
        void LoadISOMap();
        void ProcessInput(const struct InputState& state) override;
    private: 
        SDL_Texture* mTileMapTexture;
        std::vector<ISOObject> mStaticBuffer;   // sorted 1 lần khi map load
        std::vector<ISOObject> mDynamicBuffer;  // sort mỗi frame
        bool mStaticSorted = false;
        bool mDynamicSorted = false;
        int mSelectedX;
        int mSelectedY;
        int mMap[MAP_RENDER_SIZE][MAP_RENDER_SIZE] = {};
};