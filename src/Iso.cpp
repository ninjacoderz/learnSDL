#include "Defs.h"
#include "Structs.h"
#include <math.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"

#define ISO_RENDER_SPEED 15
#define MAX_ISO_OBJECTS  1024

static double    drawTimer;
static int       numISOObjects;
static ISOObject isoObjects[MAX_ISO_OBJECTS];

void initISORender(void)
{
    drawTimer = 0;
}

void doISOObjects(float deltaTime)
{
	drawTimer = MIN(drawTimer + ISO_RENDER_SPEED * deltaTime, numISOObjects);

	// uncomment the line below to draw the scene instantly each time
	// drawTimer = numISOObjects;
}

void drawISOObjects(SDL_Renderer* renderer)
{
    int i;
    ISOObject *o;

    qsort(isoObjects, numISOObjects, sizeof(ISOObject), drawComparator);

    for (i = 0 ; i < numISOObjects ; i++)
    {
        if (drawTimer >= i)
        {
            o = &isoObjects[i];

            blitAtlasImage(renderer, o->texture, o->sx, o->sy, 0, SDL_FLIP_NONE);
        }
    }
}

static int drawComparator(const void *a, const void *b)
{
	ISOObject *o1, *o2;

	o1 = (ISOObject *)a;
	o2 = (ISOObject *)b;

	return o1->y - o2->y;
}

void blitAtlasImage(SDL_Renderer* renderer, AtlasImage *atlasImage, int x, int y, int center, SDL_FlipMode flip)
{
    SDL_FRect dest;

    dest.x = x;
    dest.y = y;
    dest.w = atlasImage->rect.w;
    dest.h = atlasImage->rect.h;

    if (center)
    {
        dest.x -= dest.w / 2;
        dest.y -= dest.h / 2;
    }

    SDL_RenderTextureRotated(renderer,
                             atlasImage->texture,
                             &atlasImage->rect,   
                             &dest,               
                             0.0,                 
                             NULL,                
                             flip);               
}


void clearISOObjects(void)
{
    memset(&isoObjects, 0, sizeof(ISOObject) * numISOObjects);

    numISOObjects = 0;
}

void toISO(int x, int y, int *sx, int *sy)
{
    *sx = MAP_RENDER_OFFSET_X + ((x * TILE_WIDTH / 2) + (y * TILE_WIDTH / 2));
    *sy = MAP_RENDER_OFFSET_Y + ((y * TILE_HEIGHT / 2) - (x * TILE_HEIGHT / 2));
}

void addISOObject(int x, int z, int sx, int sy, AtlasImage *texture)
{
    ISOObject *o;

    if (numISOObjects < MAX_ISO_OBJECTS)
    {
        o = &isoObjects[numISOObjects++];

        toISO(x, z, &o->x, &o->y);

        o->sx = o->x + sx;
        o->sy = o->y + sy;
        o->texture = texture;
    }
}