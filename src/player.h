#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "entity.h"
#include "vector2.h"
#include "sprites.h"
#include "tilemap.h"
#include "sourcePrint.h"
#include "keys.h"

#define MOVE_KEYS_NUM 4

typedef enum EnumKeys {
  PLAYER_MOVE_UP,
  PLAYER_MOVE_RIGHT,
  PLAYER_MOVE_DOWN,
  PLAYER_MOVE_LEFT
} Keys;

typedef struct StructPlayer {
	Entity *entity;
	SpriteNode *spriteNode;
} Player;

void playerInitialize(void);
void playerEvent(SDL_Event *event);
void playerLoop(void);

#endif
