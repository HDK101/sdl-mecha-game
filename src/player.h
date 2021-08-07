#ifndef PLAYER_H
#define PLAYER_H


#include <SDL2/SDL.h>
#include "vector2.h";
#include "sprites.h";

typedef struct StructPlayer {
	Vector2 position;
	double health;
	double maxHealth;
} Player;

void playerInitialize(void);
void playerEvent(SDL_Event *event);

#endif
