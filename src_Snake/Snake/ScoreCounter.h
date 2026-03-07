//
// Created by Binh Nguyen Thanh on 3/3/26.
//

#ifndef MINESWEEPER_SCORECOUNTER_H
#define MINESWEEPER_SCORECOUNTER_H

#pragma once
#include <SDL3/SDL.h>
#include "Assets.h"
#include "Engine/Text.h"

using namespace Config;
class ScoreCounter {
public:
    ScoreCounter(Assets& assets): assets(assets) {};
    void Render(SDL_Surface* Surface) {
        SDL_FillSurfaceRect(Surface, &BackgroundRect,
          SDL_MapRGB(
            SDL_GetPixelFormatDetails(Surface->format),
            nullptr,
            SCORE_BACKGROUND_COLOR.r,
            SCORE_BACKGROUND_COLOR.g,
            SCORE_BACKGROUND_COLOR.b
          )
        );

        assets.Apple.Render(Surface, &AppleRect);
        Text.Render(Surface, &TextRect);
    }
    void HandleEvent( const SDL_Event& event) {
        if (event.type == UserEvents::APPLE_EATEN) {
            ++CurrentScore;
            Text.SetText(GetScoreString());
        } else if (event.type == UserEvents::RESTART_GAME) {
            CurrentScore = 0;
            Text.SetText(GetScoreString());
        }
    };
private:
    int CurrentScore = 0;
    int MaxScore = MAX_LENGTH - 2;
    Engine::Text Text = Engine::Text ( GetScoreString(), 40 );

    Assets& assets;

    std::string GetScoreString() const {

        return std::to_string(CurrentScore) + "/"
          + std::to_string(MaxScore);
    }
    SDL_Rect BackgroundRect{
        Config::PADDING,
        Config::GRID_HEIGHT + Config::PADDING * 2,
        MaxScore > 99 ? 250 : 190,
        Config::FOOTER_HEIGHT - Config::PADDING
      };

    SDL_Rect AppleRect{
        BackgroundRect.x + Config::PADDING,
        BackgroundRect.y + Config::PADDING,
        BackgroundRect.h - Config::PADDING * 2,
        BackgroundRect.h - Config::PADDING * 2
      };

    SDL_Rect TextRect{
        AppleRect.x + AppleRect.w + Config::PADDING,
        AppleRect.y,
        0, 0
      };
};

#endif //MINESWEEPER_SCORECOUNTER_H