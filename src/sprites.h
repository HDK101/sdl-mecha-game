#ifndef SPRITES_H
#define SPRITES_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vector2.h";
#include "hash.h";
#include "sourcePrint.h";
#include "renderer.h";

typedef struct SpriteNodeStruct {
	Vector2 position;
	Vector2 size;
	bool visible;
	bool queueToDestroy;
	bool originCenter;
	bool flip;
	int angle;
	SDL_Texture *texture;
} SpriteNode;

void spritesLazyStart();

void spritesAdd(SDL_Texture *texture, char *id);

void spritesDestroy(void);

void spritesActiveAdd(SpriteNode *spriteNode);

void spritesRender(void);

SpriteNode* spritesCreateNode(char *textureName);

SDL_Texture *spritesLoadTexture(char *filePath);

void spritesActiveDestroy(void);

#endif
