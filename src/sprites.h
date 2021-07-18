#ifndef SPRITES_H
#define SPRITES_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

#include "hash.h"
#include "sourcePrint.h";
#include "renderer.h";

typedef struct SpriteNodeStruct {
	double x;
	double y;
} SpriteNode;

void spritesLazyStart();

void spritesAdd(SDL_Texture *texture, char *id);

void spritesDestroy();

SDL_Texture *spritesLoadTexture(char *filePath);

#endif
