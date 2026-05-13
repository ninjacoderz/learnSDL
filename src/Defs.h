#pragma once

#define STRCPY(dest, src)             \
	strncpy(dest, src, sizeof(dest)); \
	dest[sizeof(dest) - 1] = '\0'
#define STRNCPY(dest, src, n) \
	strncpy(dest, src, n);    \
	dest[n - 1] = '\0'

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MAX_FILENAME_LENGTH    256

#define SCREEN_WIDTH  1600
#define SCREEN_HEIGHT 900

#define MAP_RENDER_OFFSET_X ((SCREEN_WIDTH - (TILE_WIDTH * MAP_RENDER_SIZE)) / 2)
#define MAP_RENDER_OFFSET_Y 425

#define MAX_MOUSE_BUTTONS 8

#define MAX_KEYBOARD_KEYS 350

#define NUM_ATLAS_BUCKETS 64

#define MAP_SIZE                  24

#define TILE_HEIGHT               30
#define TILE_WIDTH                60

#define MAP_RENDER_SIZE           24

#define FPS        60.0
#define LOGIC_RATE (FPS / 1000)

enum
{
	TEXT_ALIGN_LEFT,
	TEXT_ALIGN_CENTER,
	TEXT_ALIGN_RIGHT
};

enum
{
	SND_MAX = 32
};
