
#include "Map.cpp"
static void logic(void);
static void draw(void);

void initWorld(void)
{
	initMap();
	initISORender();
}

static void logic(void)
{
	doISOObjects();
}

static void draw(SDL_Renderer* renderer)
{
	clearISOObjects();
	addISOObjects();
	drawISOObjects(renderer);
}
