/*
 * Copyright (C) 2022 Parallel Realities. All rights reserved.
 */
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <time.h>

#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/sound.h"
#include "../system/text.h"
#include "init.h"

extern App app;

void initSDL(void)
{
	int rendererFlags, windowFlags;

	rendererFlags = 0;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	if (MIX_CreateMixerDevice(44100, SDL_AUDIO_S16, 2) < 0)
	{
		SDL_Log("Couldn't initialize SDL Mixer: %s", Mix_GetError());
		exit(1);
	}

	Mix_ReserveChannels(2);

	app.window = SDL_CreateWindow("SDL2 Isometric 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);


	if (TTF_Init() < 0)
	{
		printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_ShowCursor(0);
}

void initGameSystem(void)
{
	srand(time(NULL));

	initAtlas();

	initDraw();

	initFonts();

	initSound();

	app.dev.showFPS = 0;
}

void cleanup(void)
{
	SDL_DestroyRenderer(app.renderer);

	SDL_DestroyWindow(app.window);

	SDL_Quit();
}
